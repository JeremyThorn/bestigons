#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <signal.h>
#include "matrix_stuff.hpp"
#include "data_structures.hpp"
#include "cell.hpp"
#include "gamemaster.hpp"



Gamemaster::Gamemaster(Gamemaster_data* gamemaster_data){
  renderer = gamemaster_data->renderer;
  WIDTH = gamemaster_data->WIDTH;
  HEIGHT = gamemaster_data->HEIGHT;
  xoff = WIDTH/2;
  yoff = HEIGHT/2;
  scale = gamemaster_data->scale;
  transform = gamemaster_data->transform;
  offset_n_scale = gamemaster_data->offset_n_scale;
  selected_cell = nullptr;
}

void Gamemaster::add_cell(Cell* cell){
  cells.push_back(cell);
}


void Gamemaster::draw_self(SDL_Texture* texture, SDL_Texture* selector_texture){
  for(Cell* cell : cells){
    cell->draw_self(texture, scale, xoff, yoff, angle);
    if(cell == selected_cell){
      if (selected_cell != nullptr){
        selected_cell->draw_selector(selector_texture, scale, xoff, yoff, angle);
      }
    }
  }
}

void Gamemaster::sort_cells(){
  std::sort(cells.begin(),cells.end(),comp_cell_y);

}

void Gamemaster::get_transform(Matrix22* out_transform){
  out_transform->a = transform.a;
  out_transform->b = transform.b;
  out_transform->c = transform.c;
  out_transform->d = transform.d;
}

void Gamemaster::set_transform(Matrix22 in_transform){
  transform.a = in_transform.a;
  transform.b = in_transform.b;
  transform.c = in_transform.c;
  transform.d = in_transform.d;
}

void Gamemaster::give_transform(){
  for(Cell* cell : cells){
    cell->set_transform(transform);
  }
}

void Gamemaster::give_offset_n_scale(){
  for(Cell* cell : cells){
    cell->set_offset_n_scale(offset_n_scale);
  }
}

void Gamemaster::give_trans_n_offset_n_scale(){
  for(Cell* cell : cells){
    cell->set_transform(transform);
    cell->set_offset_n_scale(offset_n_scale);
  }
}


void Gamemaster::zoom(double in_zoom, Vec2 zoom_vec){
  transform = transform*in_zoom;
  offset_n_scale = in_zoom*offset_n_scale + (-in_zoom+1)*zoom_vec;
  scale = scale*in_zoom;
  give_trans_n_offset_n_scale();
  sort_cells();
}

void Gamemaster::set_offset(Vec2 in_offset){
  offset_n_scale = offset_n_scale + in_offset;
  give_offset_n_scale();
  sort_cells();
}

void Gamemaster::rotate(double in_angle,Vec2 rot_p){
  angle = angle+in_angle;
  if(angle > M_PI*2){
    angle = angle - M_PI*2;
  }
  if(angle < 0){
    angle = angle + M_PI*2;
  }

  Matrix22 rot_mat = {cos(-in_angle), sin(-in_angle), -sin(-in_angle), cos(-in_angle)};
  transform = rot_mat*transform;
  offset_n_scale = rot_mat*offset_n_scale - rot_mat*rot_p + rot_p;
  give_trans_n_offset_n_scale();
  sort_cells();
}

void Gamemaster::round_to_cell(Vec2* gridpos){
  double s = sqrt(3.0);
  double l = 1.0/(s*sqrt(3.0/2.0));
  double g = atan(s*sqrt(3.0))+2.0*atan(1.0/(s*sqrt(3.0)));
  double t = tan(g);
  double m1 = (1.0+t)/(1.0-t);
  double m2 = (1.0-t)/(1.0+t);
  double x1 = sqrt(3.0/8.0)*s*l;
  double x2 = l/sqrt(2.0);
  double dAx = -(m1*x2-x2);
  double dAy = 2.0*(m1*x2-x2);
  double dBx = -2.0*(m2*x2-x2);
  double dBy = (m2*x2-x2);
  double dC = -2.0*x1;
  double x = gridpos->x; double y = gridpos->y;
  double Al = m1*x+m1*x2-x2; double Ah = m1*x-m1*x2+x2;
  double Bl = m2*x+m2*x2-x2; double Bh = m2*x-m2*x2+x2;
  double Cl = x - 2.0*x1; double Ch = x + 2.0*x1;

  bool got_it = false;
  //Vec2 selected_coord = {0.0, 0.0};
  double row = -15.0; double col = -15.0;
  double max_row = 15.0; double max_col = 15.0;
  while(got_it == false){
    if(y > Al + col*dAx + row*dAy && y <= Ah + col*dAx + row*dAy &&
       y > Bl + col*dBx + row*dBy && y <= Bh + col*dBx + row*dBy &&
       y > Cl + col*dC + row*dC && y <= Ch + col*dC + row*dC){
      got_it = true;
      gridpos->x = col; gridpos->y = -row;
    }
    else{
      col += 1.0;
      if(col > max_col){
        row += 1.0;
        col = -15.0;
        if(row > max_row){
          //std::cout << "Failed to find cell." << std::endl;
          break;
        }
      }
    }
  }
}

void Gamemaster::get_clicked(Vec2 mousepos){
  /*
  double s = sqrt(3.0);
  double l = 1.0/(s*sqrt(3.0/2.0));
  double g = atan(s*sqrt(3.0))+2.0*atan(1.0/(s*sqrt(3.0)));
  double t = tan(g);
  double m1 = (1.0+t)/(1.0-t);
  double m2 = (1.0-t)/(1.0+t);
  double x1 = sqrt(3.0/8.0)*s*l;
  double x2 = l/sqrt(2.0);
  double dAx = -(m1*x2-x2);
  double dAy = 2.0*(m1*x2-x2);
  double dBx = -2.0*(m2*x2-x2);
  double dBy = (m2*x2-x2);
  double dC = -2.0*x1;*/
  Vec2 down_step_screen_space = {0.0, scale*sqrt(3.0)};
  Vec2 right_step_screen_space = {1.0*scale, 0.5*scale*sqrt(3.0)};
  Vec2 left_step_screen_space = {-1.0*scale, 0.5*scale*sqrt(3.0)};

  Vec2 down_step_grid_space = invert(transform)*(down_step_screen_space);
  Vec2 right_step_grid_space = invert(transform)*(right_step_screen_space);
  Vec2 left_step_grid_space = invert(transform)*(left_step_screen_space);
  Vec2 proj_dsgs = down_step_grid_space;
  Vec2 proj_rsgs = right_step_grid_space;
  Vec2 proj_lsgs = left_step_grid_space;
  round_to_cell(&down_step_grid_space);
  round_to_cell(&right_step_grid_space);
  round_to_cell(&left_step_grid_space);
  /*
  std::cout << down_step_grid_space << std::endl;
  double x = down_step_grid_space.x; double y = down_step_grid_space.y;
  double Al = m1*x+m1*x2-x2; double Ah = m1*x-m1*x2+x2;
  double Bl = m2*x+m2*x2-x2; double Bh = m2*x-m2*x2+x2;
  double Cl = x - 2.0*x1; double Ch = x + 2.0*x1;

  bool got_it = false;
  //Vec2 selected_coord = {0.0, 0.0};
  double row = -15.0; double col = -15.0;
  double max_row = 15.0; double max_col = 15.0;
  while(got_it == false){
    if(y > Al + col*dAx + row*dAy && y <= Ah + col*dAx + row*dAy &&
       y > Bl + col*dBx + row*dBy && y <= Bh + col*dBx + row*dBy &&
       y > Cl + col*dC + row*dC && y <= Ch + col*dC + row*dC){
      got_it = true;
      down_step_grid_space.x = col; down_step_grid_space.y = -row;
    }
    else{
      col += 1.0;
      if(col > max_col){
        row += 1.0;
        col = -15.0;
        if(row > max_row){
          //std::cout << "Failed to find cell." << std::endl;
          break;
        }
      }
    }
  }
  */
  //These two lines are to rescale sp that we a relative to the center of the
  //hex, rather than the top left hand corner (where the rect cood is).
  //mousepos.x -= scale;
  //mousepos.y -= scale*sqrt(3)/2;
  //Transform to grid space.
  Vec2 grid_coord = invert(transform)*(mousepos - offset_n_scale);
  round_to_cell(&grid_coord);
  //std::cout << grid_coord << std::endl;

   /*x = grid_coord.x;  y = grid_coord.y;
   Al = m1*x+m1*x2-x2;  Ah = m1*x-m1*x2+x2;
   Bl = m2*x+m2*x2-x2;  Bh = m2*x-m2*x2+x2;
   Cl = x - 2.0*x1;  Ch = x + 2.0*x1;

   got_it = false;
  //Vec2 selected_coord = {0.0, 0.0};
   row = -15.0;  col = -15.0;
   max_row = 15.0;  max_col = 15.0;
  while(got_it == false){
    if(y > Al + col*dAx + row*dAy && y <= Ah + col*dAx + row*dAy &&
       y > Bl + col*dBx + row*dBy && y <= Bh + col*dBx + row*dBy &&
       y > Cl + col*dC + row*dC && y <= Ch + col*dC + row*dC){
      got_it = true;
      grid_coord.x = col; grid_coord.y = -row;
    }
    else{
      col += 1.0;
      if(col > max_col){
        row += 1.0;
        col = -15.0;
        if(row > max_row){
          //std::cout << "Failed to find cell." << std::endl;
          break;
        }
      }
    }
  }*/



  //selected_coord.x = (double)col*2*x1; selected_coord.y = (double)row*2*x1;
  //std::cout << selected_coord << std::endl;
  //grid_coord.x=round(grid_coord.x); grid_coord.y=round(grid_coord.y);

  //std::cout << grid_coord << std::endl;
  //Vec2 step_down_line = {-1, 1};
  //Vec2 left_offset = {0, 1};
  //Vec2 right_offset = {-1, 0};
  std::cout <<proj_dsgs << " " << proj_rsgs << " " << proj_lsgs << std::endl;
  std::cout << grid_coord << " " <<down_step_grid_space << " " << right_step_grid_space << " " << left_step_grid_space << std::endl;
  std::vector<Vec2> line;
  for(int i = 3; i >= -3; i--){
    line.push_back(grid_coord+(double)i*down_step_grid_space);
    if (down_step_grid_space != left_step_grid_space){
      line.push_back(grid_coord+(double)i*down_step_grid_space + left_step_grid_space);
    }
    if (down_step_grid_space != right_step_grid_space){
      line.push_back(grid_coord+(double)i*down_step_grid_space + right_step_grid_space);
    }
  }
  //std::cout << std::endl;
  //for(Vec2 coord : line){
  //  std::cout << coord << std::endl;
  //}
  std::cout << "before" << std::endl;
  for(Vec2 coord : line){
    std::cout << coord << std::endl;
  }
  std::sort(line.begin(),line.end(), [proj_dsgs, proj_rsgs, proj_lsgs](const Vec2& v1, const Vec2& v2) -> bool
    {
        double comp1 = dot(v1, proj_dsgs) - dot(v2, proj_dsgs);
        if (comp1 == 0.0){
          double comp2 = dot(v1, proj_rsgs) - dot(v2, proj_rsgs);
          if (comp2 == 0.0){
            double comp3 = dot(v1, proj_lsgs) - dot(v2, proj_lsgs);
            if (comp3 == 0.0){
              return comp3 > 0;
            }
            else{
              return v1.x + v1.y > v2.x + v2.y;
            }
          }
          else{
            return comp2 > 0;
          }
        }
        else{
          return comp1 > 0;
        }
    });//, comp_cell_axis(down_step_grid_space));
  std::cout << "after" << std::endl;
  for(Vec2 coord : line){
    std::cout << coord << std::endl;
  }
  //auto old_it = cells.begin();
  //Cell* selected_cell;
  for(Vec2 coord : line){

    const auto it = find_if(cells.begin(), cells.end(), [coord](const Cell* cell) {return cell->return_coords() == coord;});

    if (it != cells.end())
    {
      //std::cout << std::endl;
      Vec2 test_coords;
      double test_height;
      (*it)->get_coords(&test_coords);
      (*it)->get_height(&test_height);
      //std::cout << test_height << std::endl;
      Vec2 height_mousepos = {mousepos.x, mousepos.y+test_height*scale/50};
      Vec2 test_grid_coord = invert(transform)*(height_mousepos - offset_n_scale);
      round_to_cell(&test_grid_coord);
      /*
      x = test_grid_coord.x; y = test_grid_coord.y;
      Al = m1*x+m1*x2-x2; Ah = m1*x-m1*x2+x2;
      Bl = m2*x+m2*x2-x2; Bh = m2*x-m2*x2+x2;
      Cl = x - 2.0*x1; Ch = x + 2.0*x1;

      got_it = false;
      //Vec2 selected_coord = {0.0, 0.0};
      row = -15.0; col = -15.0;
      max_row = 15.0; max_col = 15.0;
      while(got_it == false){
        if(y > Al + col*dAx + row*dAy && y <= Ah + col*dAx + row*dAy &&
           y > Bl + col*dBx + row*dBy && y <= Bh + col*dBx + row*dBy &&
           y > Cl + col*dC + row*dC && y <= Ch + col*dC + row*dC){
          got_it = true;
          test_grid_coord.x = col; test_grid_coord.y = -row;
        }
        else{
          col += 1.0;
          if(col > max_col){
            row += 1.0;
            col = -15.0;
            if(row > max_row){
              //std::cout << "Failed to find cell." << std::endl;
              selected_cell = nullptr;
              break;
            }
          }
        }
      }*/


      //std::cout << test_grid_coord << std::endl;
      //std::cout << height_mousepos << std::endl;
      //std::cout << test_coords << std::endl;
      if (test_grid_coord == test_coords){
        std::cout << "selected coord: " <<test_coords << std::endl;
        selected_cell = (*it);
        break;
      }
      else{
        selected_cell = nullptr;
        //break;
      }
      //old_it = it;
    }
  }

}
