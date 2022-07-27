#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

//gcc t.c $(pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5 --libs --cflags) -lm

const int width = 1200;
const int height = 640;
const int half_width = width / 2;
const int half_height = height / 2;
const float font_size = (225.0 / 8.0) * ((float) width / height);

void must_init(bool test, const char* description){

  if(test) return;

  printf("couldn't initialize %s\n", description);
  exit(1);

}

void inits(){

  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");
  must_init(al_install_mouse(), "mouse");
  must_init(al_init_primitives_addon(), "primitives");
  must_init(al_init_font_addon(), "font addons");
  must_init(al_init_ttf_addon(), "ttf font");

}

void event_register(ALLEGRO_EVENT_QUEUE* queue,  ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer){

  al_register_event_source(queue, al_get_mouse_event_source());
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));

}

void update_color(ALLEGRO_COLOR button_colors[], int i, bool selected){

  button_colors[i] = selected ? al_map_rgb(100, 100, 100) : al_map_rgb(215, 188, 134);
   
}

void updateConstant(float* k, float* r, float i){
  *k += i;
  *r += i;
}

void draw_menu(ALLEGRO_FONT* font, float rect_x_pos1, float rect_x_pos2, float rect_y_size,
               float rect_y_pos1, float rect_y_pos2, float rect_y_pos3, float rect_y_pos4,
               ALLEGRO_COLOR button_colors[]){

  float k = 4.0;
  float r = 3.0;

  al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(215, 188, 134));
  al_draw_rectangle(width * 0.01, height * 0.01, width * 0.99, height * 0.99, al_map_rgb(0,0,0), 5);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos1, rect_x_pos2, rect_y_pos1 + rect_y_size, button_colors[0]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos1 * k / r, ALLEGRO_ALIGN_CENTRE, "NEW GAME");
  al_draw_rectangle(rect_x_pos1, rect_y_pos1, rect_x_pos2, rect_y_pos1 + rect_y_size, al_map_rgb(0,0,0), 2);
  updateConstant(&k, &r, 4.0);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos2, rect_x_pos2, rect_y_pos2 + rect_y_size, button_colors[1]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos2 * k / r, ALLEGRO_ALIGN_CENTRE, "SETTINGS");
  al_draw_rectangle(rect_x_pos1, rect_y_pos2, rect_x_pos2, rect_y_pos2 + rect_y_size, al_map_rgb(0,0,0), 2); 
  updateConstant(&k, &r, 4.0);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos3, rect_x_pos2, rect_y_pos3 + rect_y_size, button_colors[2]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos3 * k / r, ALLEGRO_ALIGN_CENTRE, "HELP");
  al_draw_rectangle(rect_x_pos1, rect_y_pos3, rect_x_pos2, rect_y_pos3 + rect_y_size, al_map_rgb(0,0,0), 2);  
  updateConstant(&k, &r, 4.0);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos4, rect_x_pos2, rect_y_pos4 + rect_y_size, button_colors[3]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos4 * k / r, ALLEGRO_ALIGN_CENTRE, "QUIT");
  al_draw_rectangle(rect_x_pos1, rect_y_pos4, rect_x_pos2, rect_y_pos4 + rect_y_size, al_map_rgb(0,0,0), 2);  

}

void menu(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font,
          bool* game, bool* redraw, int* screen, ALLEGRO_COLOR button_colors[]){

  float rect_x_pos1 = width * 0.35;
  float rect_x_pos2 = 0.3 * width + rect_x_pos1;
  float rect_y_size = font_size + height * 0.10;
  float rect_y_pos1 = height * 0.15;
  float rect_y_pos2 = height * 0.35;
  float rect_y_pos3 = height * 0.55;
  float rect_y_pos4 = height * 0.75;

  switch (event.type){

    case ALLEGRO_EVENT_TIMER:
      *redraw = true;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      *game = false;
      break;

    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      if(event.mouse.x >= rect_x_pos1 && event.mouse.x <= rect_x_pos2){

        if(event.mouse.y >= rect_y_pos1 && event.mouse.y <= rect_y_pos1 + rect_y_size)
          *screen = 1;
        if(event.mouse.y >= rect_y_pos2 && event.mouse.y <= rect_y_pos2 + rect_y_size)
          *screen = 3;
        if(event.mouse.y >= rect_y_pos3 && event.mouse.y <= rect_y_pos3 + rect_y_size)
          *screen = 4;
        if(event.mouse.y >= rect_y_pos4 && event.mouse.y <= rect_y_pos4 + rect_y_size)
          *screen = 5;                

      }      
      break;

    case ALLEGRO_EVENT_MOUSE_AXES:

      if(event.mouse.x >= rect_x_pos1 && event.mouse.x <= rect_x_pos2 &&
         event.mouse.y >= rect_y_pos1 && event.mouse.y <= rect_y_pos1 + rect_y_size)
        update_color(button_colors, 0, true);
      else update_color(button_colors, 0, false);
      if(event.mouse.x >= rect_x_pos1 && event.mouse.x <= rect_x_pos2 &&
         event.mouse.y >= rect_y_pos2 && event.mouse.y <= rect_y_pos2 + rect_y_size)
        update_color(button_colors, 1, true);
      else update_color(button_colors, 1, false);    
      if(event.mouse.x >= rect_x_pos1 && event.mouse.x <= rect_x_pos2 &&
         event.mouse.y >= rect_y_pos3 && event.mouse.y <= rect_y_pos3 + rect_y_size)
        update_color(button_colors, 2, true);
      else update_color(button_colors, 2, false);      
      if(event.mouse.x >= rect_x_pos1 && event.mouse.x <= rect_x_pos2 &&
         event.mouse.y >= rect_y_pos4 && event.mouse.y <= rect_y_pos4 + rect_y_size)
        update_color(button_colors, 3, true);                                                   
      else update_color(button_colors, 3, false);        
      break; 
        
   }

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 0){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    draw_menu(font, rect_x_pos1, rect_x_pos2, rect_y_size, rect_y_pos1,
              rect_y_pos2, rect_y_pos3, rect_y_pos4, button_colors);
    al_flip_display();

    *redraw = false;
  }

}

void draw_difficulty(ALLEGRO_FONT* font, float rect_x_pos1, float rect_x_pos2, float rect_y_size,
                     float rect_y_pos1, float rect_y_pos2, float rect_y_pos3, ALLEGRO_COLOR button_colors[]){

  float k = 9.0;
  float r = 7.0;

  al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(215, 188, 134));
  al_draw_rectangle(width * 0.01, height * 0.01, width * 0.99, height * 0.99, al_map_rgb(0, 0, 0), 5);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos1, rect_x_pos2, rect_y_pos1 + rect_y_size, button_colors[4]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos1 * k / r, ALLEGRO_ALIGN_CENTRE, "EASY");
  al_draw_rectangle(rect_x_pos1, rect_y_pos1, rect_x_pos2, rect_y_pos1 + rect_y_size, al_map_rgb(0, 0, 0), 2);
  updateConstant(&k, &r, 9.0);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos2, rect_x_pos2, rect_y_pos2 + rect_y_size, button_colors[5]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos2 * k / r, ALLEGRO_ALIGN_CENTRE, "MEDIUM");
  al_draw_rectangle(rect_x_pos1, rect_y_pos2, rect_x_pos2, rect_y_pos2 + rect_y_size, al_map_rgb(0, 0, 0), 2); 
  updateConstant(&k, &r, 9.0);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos3, rect_x_pos2, rect_y_pos3 + rect_y_size, button_colors[6]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos3 * k / r, ALLEGRO_ALIGN_CENTRE, "HARD");
  al_draw_rectangle(rect_x_pos1, rect_y_pos3, rect_x_pos2, rect_y_pos3 + rect_y_size, al_map_rgb(0, 0, 0), 2);  

}

void set_difficulty(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_KEYBOARD_STATE keyboard,
                    ALLEGRO_FONT* font, ALLEGRO_TIMER* timer, bool* game, bool* redraw, int* screen, int* difficulty,
                    ALLEGRO_COLOR button_colors[]){

  float rect_x_pos1 = width * 0.40;
  float rect_x_pos2 = width * 0.60;
  float rect_y_size = font_size + height * 0.10;
  float rect_y_pos1 = height * 0.175;
  float rect_y_pos2 = height * 0.375;
  float rect_y_pos3 = height * 0.575;  

  switch (event.type){

    case ALLEGRO_EVENT_TIMER:
      *redraw = true;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      *game = false;
      break;

    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      if(event.mouse.x >= rect_x_pos1 && event.mouse.x <= rect_x_pos2){

        if(event.mouse.y >= rect_y_pos1 && event.mouse.y <= rect_y_pos1 + rect_y_size)
          *difficulty = 1;
        if(event.mouse.y >= rect_y_pos2 && event.mouse.y <= rect_y_pos2 + rect_y_size)
          *difficulty = 2;
        if(event.mouse.y >= rect_y_pos3 && event.mouse.y <= rect_y_pos3 + rect_y_size)
          *difficulty = 3;               

      }      
      break;

    case ALLEGRO_EVENT_MOUSE_AXES:

      if(event.mouse.x >= rect_x_pos1 && event.mouse.x <= rect_x_pos2 &&
         event.mouse.y >= rect_y_pos1 && event.mouse.y <= rect_y_pos1 + rect_y_size)
        update_color(button_colors, 4, true);
      else update_color(button_colors, 4, false);
      if(event.mouse.x >= rect_x_pos1 && event.mouse.x <= rect_x_pos2 &&
         event.mouse.y >= rect_y_pos2 && event.mouse.y <= rect_y_pos2 + rect_y_size)
        update_color(button_colors, 5, true);
      else update_color(button_colors, 5, false);    
      if(event.mouse.x >= rect_x_pos1 && event.mouse.x <= rect_x_pos2 &&
         event.mouse.y >= rect_y_pos3 && event.mouse.y <= rect_y_pos3 + rect_y_size)
        update_color(button_colors, 6, true);
      else update_color(button_colors, 6, false);             
      break;     
   }

  *screen = *difficulty == 0 ? *screen : 2; 
  if(*screen == 2) al_set_timer_count(timer, 0);

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 1){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    draw_difficulty(font, rect_x_pos1, rect_x_pos2,
                    rect_y_size, rect_y_pos1,
                    rect_y_pos2, rect_y_pos3, button_colors);
    al_flip_display();

    *redraw = false;
  } 

}

void armor_logic(bool* armor){

  *armor = true;

}

struct shot_properties{

  int radius;

  float pos_x;
  float pos_y;

  float x_velocity;
  float y_velocity;

  ALLEGRO_COLOR color;
  bool alive;

};

void shots_colision(struct shot_properties* shot){

  if(shot->pos_x > width || shot->pos_x < 0 ||
     shot->pos_y > height || shot->pos_y < 0) shot->alive = false;  

}

void shots_generation(struct shot_properties* shot, float* shield, float gun_size, float* player_radius){

  shot->radius = 5;

  shot->pos_x = (*player_radius + gun_size) * (-cos(*shield + M_PI / 2)) + half_width;
  shot->pos_y = (*player_radius + gun_size) * (-sin(*shield + M_PI / 2)) + half_height;
  
  shot->x_velocity = shot->pos_x - half_width;
  shot->y_velocity = shot->pos_y - half_height;

  shot->color = al_map_rgb(255, 0, 0);
  shot->alive = true;

}

void shots_movement(struct shot_properties* shot){

  float speed = 0.2;

  shot->pos_x += shot->x_velocity * speed;
  shot->pos_y += shot->y_velocity * speed;

}

void gun_logic(ALLEGRO_TIMER* timer, bool shot_fired, struct shot_properties* shot, float* shield, float gun_size,
               float* player_radius, float* delay_1s){

  if(shot_fired && !shot->alive && *delay_1s == 0){

    shots_generation(shot, shield, gun_size, player_radius);
    *delay_1s = ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10);        

  }

  if(*delay_1s + 1 <= ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10)) 
    *delay_1s = 0;

  shots_movement(shot);
  shots_colision(shot);

  if(shot->alive) al_draw_filled_circle(shot->pos_x, shot->pos_y,
                                        shot->radius, shot->color);
  
}

struct enemy{

  int radius;

  float pos_x;
  float pos_y;

  float vel_pos_x;
  float vel_pos_y;

  ALLEGRO_COLOR color;
  bool alive;

  bool ally;

};

void enemy_generation(struct enemy enemies[], int* index_enemies, int* max_enemies){

  int side = rand() % 4;
  bool axes[2];

  if(*index_enemies < *max_enemies && !enemies[*index_enemies].alive){

    switch(side){

      case 0:
        enemies[*index_enemies].pos_x = 0;
        enemies[*index_enemies].pos_y = rand() % height;
        axes[0] = true;
        axes[1] = enemies[*index_enemies].pos_y >= half_height ? false : true;
        break;

      case 1: 
        enemies[*index_enemies].pos_x = width;
        enemies[*index_enemies].pos_y =rand() % height; 
        axes[1] = enemies[*index_enemies].pos_y >= half_height ? false : true;
        axes[0] = false;
        break;

      case 2:
        enemies[*index_enemies].pos_x = rand() % width;
        enemies[*index_enemies].pos_y = 0;
        axes[1] = true;
        axes[0] = enemies[*index_enemies].pos_x >= half_width ? false : true;
        break;

      case 3: 
        enemies[*index_enemies].pos_x = rand() % width;
        enemies[*index_enemies].pos_y = height;
        axes[1] = false; 
        axes[0] = enemies[*index_enemies].pos_x >= half_width ? false : true;
        break;        

    }

    int speed_max = 10;
    int speed_min = 5;

    float speed = (float) (rand() % (speed_max - speed_min) + speed_min) / 1000;


    float x_velocity = axes[0] ? abs(enemies[*index_enemies].pos_x - half_width) * speed:
                                 -abs(enemies[*index_enemies].pos_x - half_width) * speed;

    float y_velocity = axes[1] ? abs(enemies[*index_enemies].pos_y - half_height) * speed:
                                 -abs(enemies[*index_enemies].pos_y - half_height) * speed;

    enemies[*index_enemies].vel_pos_x = x_velocity;
    enemies[*index_enemies].vel_pos_y = y_velocity;

    enemies[*index_enemies].radius = rand() % 5 + 4;

    enemies[*index_enemies].alive = true;

    *index_enemies += *index_enemies < *max_enemies - 1 ? 1 : - *max_enemies - 1;

    int probability_ally = 10;

    enemies[*index_enemies].ally = rand() % probability_ally == 0;

    enemies[*index_enemies].color = enemies[*index_enemies].ally ? al_map_rgb(0, 204, 204) : al_map_rgb(129, 0, 0);

  }

}

void movement_update(struct enemy enemies[], int i){

  enemies[i].pos_x += enemies[i].vel_pos_x;
  enemies[i].pos_y += enemies[i].vel_pos_y;

}

void colision_check(struct enemy enemies[], int i, float* shield, float* player_radius, float player_shield_radius,
                    struct shot_properties* shot, int* player_points, bool armor){

  float enemy_angle = M_PI / 2 + atan((enemies[i].pos_y - half_height) / (enemies[i].pos_x - half_width));
  enemy_angle += enemies[i].pos_x >= half_width ? M_PI : 0;
   
  enemy_angle -= enemy_angle > 3 * M_PI / 2 && *shield < M_PI / 2 ?
                 2 * M_PI : 0;
  enemy_angle += enemy_angle < M_PI / 2 && *shield > 3 * M_PI / 2 ?
                 2 * M_PI : 0;                  

  bool player_hitted = pow(half_width - enemies[i].pos_x, 2) + pow(half_height - enemies[i].pos_y, 2)
                       <= pow(*player_radius + enemies[i].radius, 2);
  bool edge_hitted = enemies[i].pos_x > width || enemies[i].pos_x < 0 ||
                     enemies[i].pos_y > height || enemies[i].pos_y < 0;
  bool shield_hitted = enemy_angle >= *shield - M_PI / 2 && enemy_angle <= *shield + M_PI / 2
                       && sqrt(pow(enemies[i].pos_x - half_width, 2) + pow(enemies[i].pos_y - half_height, 2))
                       <= enemies[i].radius + player_shield_radius
                       && sqrt(pow(enemies[i].pos_x - half_width, 2) + pow(enemies[i].pos_y - half_height, 2)) 
                       > enemies[i].radius + player_shield_radius - 10;

  if(armor && pow(half_width - enemies[i].pos_x, 2) + pow(half_height - enemies[i].pos_y, 2) <=
     pow(width / height * 60 + enemies[i].radius, 2)) shield_hitted = true;                       

  float enemy_area = M_PI * pow(enemies[i].radius, 2);
  float player_area = M_PI * pow(*player_radius, 2);

  float difference = enemies[i].ally ? player_area + enemy_area : player_area - enemy_area;                       
  float radius_change = difference > 0 ? sqrt(difference / M_PI) : 0;

  if(player_hitted) *player_radius = radius_change;

  difference = player_area + enemy_area;
  radius_change = difference > 0 ? sqrt(difference / M_PI) : 0;

  if(shield_hitted && !enemies[i].ally) (*player_points)++;

  if((player_hitted || edge_hitted || shield_hitted))
    enemies[i].alive = false;

  if(shot->alive){

    float distance = sqrt(pow(shot->pos_x - (enemies[i].pos_x), 2) +
                          pow(shot->pos_y - (enemies[i].pos_y), 2));

    if(distance <= shot->radius + enemies[i].radius){

      shot->alive = false;
      enemies[i].alive = false;
      
      if(!enemies[i].ally){
        *player_radius = radius_change;
        *player_points += 2;
      }

    }

  }

}

void enemy_logic(ALLEGRO_TIMER* timer, struct enemy enemies[], int* index_enemies,
                 int* max_enemies, float* mouse_pos_x, float* mouse_pos_y, float* shield,
                 float* player_radius, float player_shield_radius, struct shot_properties* shot,
                 int* player_points, bool armor){

  if(rand() % 50 == 0) enemy_generation(enemies, index_enemies, max_enemies);

  for(int i = 0; i < *max_enemies; i++){
 
    if(enemies[i].alive){

      movement_update(enemies, i); 
      colision_check(enemies, i, shield, player_radius, player_shield_radius,
                     shot, player_points, armor);

      al_draw_filled_circle(enemies[i].pos_x, enemies[i].pos_y,
                            enemies[i].radius, enemies[i].color);
      }

  }
  
}

void game_background(ALLEGRO_FONT* font, ALLEGRO_TIMER* timer, float* player_radius, float player_shield_radius, float* shield,
                     float* mouse_pos_x, float* mouse_pos_y, float gun_size, int* player_life, int* player_points, bool armor){

  *shield = M_PI / 2 + atan(*mouse_pos_y / *mouse_pos_x);
  *shield += *mouse_pos_x >= 0 ? M_PI : 0;

  float gun_point_1_x = (*player_radius + gun_size) * (-cos(*shield + M_PI / 2)) + half_width;
  float gun_point_1_y = (*player_radius + gun_size) * (-sin(*shield + M_PI / 2)) + half_height;

  float gun_point_2_x = *player_radius * (-cos(*shield + 5 + M_PI / 2)) + half_width;
  float gun_point_2_y = *player_radius * (-sin(*shield + 5 + M_PI / 2)) + half_height;

  float gun_point_3_x = *player_radius * (-cos(*shield - 5 + M_PI / 2)) + half_width;
  float gun_point_3_y = *player_radius * (-sin(*shield - 5 + M_PI / 2)) + half_height;

  must_init(al_init_image_addon(), "image addon");
  ALLEGRO_BITMAP* background = al_load_bitmap("background.png");
  must_init(background, "background");
  al_draw_bitmap(background, 0, 0, 0); 

  al_draw_filled_circle(half_width, half_height, *player_radius, al_map_rgb(0, 0, 0));
  al_draw_circle(half_width, half_height, *player_radius, al_map_rgb(0, 123, 123), 3);
  al_draw_arc(half_width, half_height, player_shield_radius, *shield, M_PI, 
              al_map_rgb(0, 0, 0), 3);
  al_draw_filled_triangle(gun_point_1_x, gun_point_1_y, gun_point_2_x, gun_point_2_y,
                          gun_point_3_x, gun_point_3_y, al_map_rgb(0, 0, 0));
  al_draw_triangle(gun_point_1_x, gun_point_1_y, gun_point_2_x, gun_point_2_y,
                          gun_point_3_x, gun_point_3_y, al_map_rgb(0, 123, 123), 3);

  if(armor) al_draw_filled_circle(half_width, half_height, player_shield_radius, al_map_rgba(0, 0, 0, 50));

  al_draw_filled_rectangle(0, 0, width, height * 0.05, al_map_rgb(0, 0, 0));
  al_draw_rectangle(0, 0, width, height * 0.05, al_map_rgb(204, 102, 0), 3);

  al_draw_textf(font, al_map_rgb(255, 255, 255), width * 0.05, 0, ALLEGRO_ALIGN_LEFT,
                "Timer: %.2f", ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10));

  al_draw_textf(font, al_map_rgb(255, 255, 255), width * 0.5, 0, ALLEGRO_ALIGN_CENTRE, "Lifes remaining: %d", *player_life);

  al_draw_textf(font, al_map_rgb(255, 255, 255), width * 0.95, 0, ALLEGRO_ALIGN_RIGHT, "Points: %d", *player_points);

  al_destroy_bitmap(background);

}

void play_game(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_KEYBOARD_STATE keyboard,
               ALLEGRO_FONT* font, ALLEGRO_TIMER* timer, bool* game, bool* redraw, int* screen,
               float* player_radius, float player_shield_radius, float* shield, float* mouse_pos_x, 
               float* mouse_pos_y, struct enemy enemies[], int* index_enemies, int* max_enemies,
               float gun_size, float* delay_1s, struct shot_properties* shot, int* player_life,
               int* player_points){

  bool shot_fired = false;
  bool armor = false;
  switch (event.type){

    case ALLEGRO_EVENT_TIMER:
      *redraw = true;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      *game = false;
      break;

    case ALLEGRO_EVENT_MOUSE_AXES:
      *mouse_pos_x = event.mouse.x - half_width;
      *mouse_pos_y = event.mouse.y - half_height; 
      break;

  }

  al_get_keyboard_state(&keyboard);
  if(al_key_down(&keyboard, ALLEGRO_KEY_SPACE))
    armor_logic(&armor); 

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 2){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    game_background(font, timer, player_radius, player_shield_radius, shield,
                    mouse_pos_x, mouse_pos_y, gun_size, player_life, player_points,
                    armor);
    enemy_logic(timer, enemies, index_enemies, max_enemies,
                mouse_pos_x, mouse_pos_y, shield, player_radius,
                player_shield_radius, shot, player_points, armor);    

    if(*player_radius <= 0 && *player_life > 0){

      *player_radius = width / height * 20;
      (*player_life)--;

    }                            
  
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    if (state.buttons & 1)
      shot_fired = true; 
    
    gun_logic(timer, shot_fired, shot, shield, gun_size, player_radius, delay_1s);
    
    al_flip_display();

    *redraw = false;
  }  
}

int main(){

  inits();

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 100.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

  ALLEGRO_DISPLAY* display = al_create_display(width, height);
  must_init(display, "display");

  ALLEGRO_FONT* font = al_load_font("font.ttf", font_size, 0);
  must_init(font, "font");

  ALLEGRO_FONT* game_font = al_load_font("game_font.ttf", font_size / 3, 0);
  must_init(game_font, "game_font");

  ALLEGRO_EVENT event;
  ALLEGRO_KEYBOARD_STATE keyboard;

  event_register(queue, display, timer);

  bool game = true, redraw = true;
  int screen = 0;
  ALLEGRO_COLOR button_colors[10];

  
  float player_shield_radius = width / height * 60;
  float shield = 0;
  float mouse_pos_x = 0;
  float mouse_pos_y = - half_height;

  float player_radius = width / height * 20;
  int player_life = 3;
  int player_points = 0;

  float gun_size = player_radius * 0.8; 
  float delay_1s = 0;

  int max_enemies = 10;
  int index_enemies = 0;
  struct enemy enemies[max_enemies];
  for(int i = 0; i < max_enemies; i++)
    enemies[i].alive = false;

  struct shot_properties shot;
  //shot.alive = false;

  time_t t;
  srand(time(&t));

  int difficulty = 0;
  al_start_timer(timer);

  while(game){

    al_wait_for_event(queue, &event);
    switch(screen){

      case 0:

        menu(event, queue, font, &game, &redraw, &screen, button_colors);
        break;

      case 1:
        
        set_difficulty(event, queue, keyboard, font, timer, &game, &redraw, &screen,
                       &difficulty, button_colors);
        break;  

      case 2: 
        
        play_game(event, queue, keyboard, game_font, timer, &game, &redraw,
                  &screen, &player_radius, player_shield_radius, &shield, &mouse_pos_x,
                  &mouse_pos_y, enemies, &index_enemies, &max_enemies, gun_size, &delay_1s,
                  &shot, &player_life, &player_points);
        break;

      case 3:

        game = false;
        break;

      case 4:

        game = false;
        break;

      case 5:

        game = false;
        break;        

      } 
  }

  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}
