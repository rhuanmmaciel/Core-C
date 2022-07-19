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

const int height = 720;
const int width = 1280;
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

void updateConstant(float* k, float* r){
  *k += 4.0;
  *r += 4.0;
}

void draw_menu(ALLEGRO_FONT* font, float rect_x_pos1, float rect_x_pos2, float rect_y_size,
               float rect_y_pos1, float rect_y_pos2, float rect_y_pos3, float rect_y_pos4){

  float k = 4.0;
  float r = 3.0;

  al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(215, 188, 134));
  al_draw_rectangle(width * 0.01, height * 0.01, width * 0.99, height * 0.99, al_map_rgb(0, 0, 0), 5);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos1 * k / r, ALLEGRO_ALIGN_CENTRE, "NEW GAME");
  al_draw_rectangle(rect_x_pos1, rect_y_pos1, rect_x_pos2, rect_y_pos1 + rect_y_size, al_map_rgb(0, 0, 0), 2);
  updateConstant(&k, &r);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos2 * k / r, ALLEGRO_ALIGN_CENTRE, "SETTINGS");
  al_draw_rectangle(rect_x_pos1, rect_y_pos2, rect_x_pos2, rect_y_pos2 + rect_y_size, al_map_rgb(0, 0, 0), 2); 
  updateConstant(&k, &r);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos3 * k / r, ALLEGRO_ALIGN_CENTRE, "HELP");
  al_draw_rectangle(rect_x_pos1, rect_y_pos3, rect_x_pos2, rect_y_pos3 + rect_y_size, al_map_rgb(0, 0, 0), 2);  
  updateConstant(&k, &r);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos4 * k / r, ALLEGRO_ALIGN_CENTRE, "QUIT");
  al_draw_rectangle(rect_x_pos1, rect_y_pos4, rect_x_pos2, rect_y_pos4 + rect_y_size, al_map_rgb(0, 0, 0), 2);  

}

void menu(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font,
          bool* game, bool* redraw, int* screen, float rect_x_pos1, float rect_x_pos2,
          float rect_y_size, float rect_y_pos1, float rect_y_pos2,
          float rect_y_pos3, float rect_y_pos4){

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
   }

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 0){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    draw_menu(font, rect_x_pos1, rect_x_pos2, rect_y_size, rect_y_pos1,
              rect_y_pos2, rect_y_pos3, rect_y_pos4);
    al_flip_display();

    *redraw = false;
  }

}

void draw_difficulty(ALLEGRO_FONT* font, float rect_x_pos1, float rect_x_pos2, float rect_y_size,
                     float rect_y_pos1, float rect_y_pos2, float rect_y_pos3){

  float k = 4.0;
  float r = 3.0;

  al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(215, 188, 134));
  al_draw_rectangle(width * 0.01, height * 0.01, width * 0.99, height * 0.99, al_map_rgb(0, 0, 0), 5);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos1 * k / r, ALLEGRO_ALIGN_CENTRE, "EASY");
  al_draw_rectangle(rect_x_pos1, rect_y_pos1, rect_x_pos2, rect_y_pos1 + rect_y_size, al_map_rgb(0, 0, 0), 2);
  updateConstant(&k, &r);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos2 * k / r, ALLEGRO_ALIGN_CENTRE, "MEDIUM");
  al_draw_rectangle(rect_x_pos1, rect_y_pos2, rect_x_pos2, rect_y_pos2 + rect_y_size, al_map_rgb(0, 0, 0), 2); 
  updateConstant(&k, &r);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos3 * k / r, ALLEGRO_ALIGN_CENTRE, "HARD");
  al_draw_rectangle(rect_x_pos1, rect_y_pos3, rect_x_pos2, rect_y_pos3 + rect_y_size, al_map_rgb(0, 0, 0), 2);  

}

void set_difficulty(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_KEYBOARD_STATE keyboard,
                    ALLEGRO_FONT* font,  bool* game, bool* redraw, int* screen, int* difficulty, 
                    float rect_x_pos1, float rect_x_pos2, float rect_y_size, float rect_y_pos1,
                    float rect_y_pos2, float rect_y_pos3){

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
   }

  *screen = *difficulty == 0 ? *screen : 2; 

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 1){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    draw_difficulty(font, rect_x_pos1, rect_x_pos2,
                    rect_y_size, rect_y_pos1,
                    rect_y_pos2, rect_y_pos3);
    al_flip_display();

    *redraw = false;
  } 

}

struct enemy{

  int radius;
  int pos_x;
  int pos_y;
  ALLEGRO_COLOR color;
  bool alive;

};

void enemy_generation(struct enemy enemies[], int* index_enemies, int* max_enemies){

  int side = rand() % 4;

  if(*index_enemies < *max_enemies && enemies[*index_enemies].alive == false){

    switch(side){

      case 0:
        enemies[*index_enemies].pos_x = 0;
        enemies[*index_enemies].pos_y = rand() % height;
        break;
      case 1: 
        enemies[*index_enemies].pos_x = width;
        enemies[*index_enemies].pos_y =rand() % height; 
        break;
      case 2:
        enemies[*index_enemies].pos_x = rand() % width;
        enemies[*index_enemies].pos_y = 0;
        break;
      case 3: 
        enemies[*index_enemies].pos_x = rand() % width;
        enemies[*index_enemies].pos_y = height; 
        break;        

    }

    enemies[*index_enemies].radius = 10;
    enemies[*index_enemies].color = al_map_rgb(0, 0, 0);
    enemies[*index_enemies].alive = true;
    *index_enemies += *index_enemies < 29 ? 1 : - 29;

  }

}

void movement_update(struct enemy enemies[], int i){

  enemies[i].pos_x += enemies[i].pos_x < width / 2 ? 1 : -1;
  enemies[i].pos_y += enemies[i].pos_y < height / 2 ? 1 : -1;

}

void colision_check(struct enemy enemies[], int x, int y, int i){

  if(enemies[i].pos_x > width / 2 && enemies[i].pos_y > height / 2)
    enemies[i].alive = false;

}

void enemy_logic(ALLEGRO_TIMER* timer, struct enemy enemies[], int* index_enemies,
                 int* max_enemies, float* mouse_pos_x, float* mouse_pos_y){

  if(al_get_timer_count(timer) % 100 == 0)enemy_generation(enemies, index_enemies, max_enemies);

  for(int i = 0; i < *max_enemies; i++){
 
    movement_update(enemies, i); 
    colision_check(enemies, *mouse_pos_x, *mouse_pos_y, i);

    if(enemies[i].alive == true)
      al_draw_filled_circle(enemies[i].pos_x, enemies[i].pos_y,
                            enemies[i].radius, enemies[i].color);
  }
  
}

void game_background(float* radius, float* shield, float* mouse_pos_x, float* mouse_pos_y){

  *shield = atan(*mouse_pos_y / *mouse_pos_x);
  *shield += *mouse_pos_x >= 0 ? M_PI : 0;

  must_init(al_init_image_addon(), "image addon");
  ALLEGRO_BITMAP* background = al_load_bitmap("background.jpg");
  must_init(background, "background");
  al_draw_bitmap(background, 0, 0, 0);
  al_draw_filled_circle(width / 2, height / 2, *radius, al_map_rgb(4, 98, 97));
  al_draw_arc(width / 2, height / 2, width / height * 60, *shield + M_PI / 2, M_PI, 
              al_map_rgb(4, 98, 97), 3);
  al_destroy_bitmap(background);

}

void play_game(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_KEYBOARD_STATE keyboard,
               ALLEGRO_FONT* font, ALLEGRO_TIMER* timer, bool* game, bool* redraw, int* screen,
               float* radius, float* shield, float* mouse_pos_x, float* mouse_pos_y, 
               struct enemy enemies[], int* index_enemies, int* max_enemies){

  switch (event.type){

    case ALLEGRO_EVENT_TIMER:
      *redraw = true;
      break;

    case ALLEGRO_EVENT_KEY_DOWN:
      /*al_get_keyboard_state(&keyboard);
      if(al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))
        enemy_logic(timer, enemies, index_enemies);*/    
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      *game = false;
      break;

    case ALLEGRO_EVENT_MOUSE_AXES:
      *mouse_pos_x = event.mouse.x - width / 2;
      *mouse_pos_y = event.mouse.y - height / 2; 
      break;
  }

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 2){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    game_background(radius, shield, mouse_pos_x, mouse_pos_y);
    enemy_logic(timer, enemies, index_enemies, max_enemies, mouse_pos_x, mouse_pos_y);
    al_flip_display();

    *redraw = false;
  }  
}

int main(){

  inits();

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
  must_init(timer, "timer");
  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");
  ALLEGRO_DISPLAY* display = al_create_display(width, height);
  must_init(display, "display");
  ALLEGRO_FONT* font = al_load_font("font.ttf", font_size, 0);
  must_init(font, "font");
  ALLEGRO_EVENT event;
  ALLEGRO_KEYBOARD_STATE keyboard;

  event_register(queue, display, timer);

  bool game = true, redraw = true;
  int screen = 0;
  float radius = width / height * 20;
  float shield = 0;
  float mouse_pos_x = 0;
  float mouse_pos_y = - height / 2;

  int max_enemies = 30;
  int index_enemies = 0;
  struct enemy enemies[max_enemies];
  for(int i = 0; i < max_enemies; i++)
    enemies[i].alive = false;

  time_t t;
  srand(time(&t));

  float menu_rect_x_pos1 = width * 0.35;
  float menu_rect_x_pos2 = 0.3 * width + menu_rect_x_pos1;
  float menu_rect_y_size = font_size + height * 0.10;
  float menu_rect_y_pos1 = height * 0.15;
  float menu_rect_y_pos2 = height * 0.35;
  float menu_rect_y_pos3 = height * 0.55;
  float menu_rect_y_pos4 = height * 0.75;

  int difficulty = 0;
  float difficulty_rect_x_pos1 = width * 0.40;
  float difficulty_rect_x_pos2 = width * 0.60;
  float difficulty_rect_y_size = font_size + height * 0.10;
  float difficulty_rect_y_pos1 = height * 0.175;
  float difficulty_rect_y_pos2 = height * 0.375;
  float difficulty_rect_y_pos3 = height * 0.575;

  al_start_timer(timer);

  while(game){

    al_wait_for_event(queue, &event);
    switch(screen){

      case 0:

        menu(event, queue, font, &game, &redraw, &screen,
            menu_rect_x_pos1, menu_rect_x_pos2, menu_rect_y_size,
            menu_rect_y_pos1, menu_rect_y_pos2, menu_rect_y_pos3,
            menu_rect_y_pos4);
        break;

      case 1:
        
        set_difficulty(event, queue, keyboard, font, &game, &redraw, &screen, &difficulty,
                       difficulty_rect_x_pos1, difficulty_rect_x_pos2, difficulty_rect_y_size,
                       difficulty_rect_y_pos1, difficulty_rect_y_pos2, difficulty_rect_y_pos3);
        break;  

      case 2: 
        
        play_game(event, queue, keyboard, font, timer, &game, &redraw,
                  &screen, &radius, &shield, &mouse_pos_x, &mouse_pos_y,
                  enemies, &index_enemies, &max_enemies);
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
