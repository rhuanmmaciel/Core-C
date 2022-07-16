#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

//teste

//gcc t.c $(pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5 --libs --cflags)

const int height = 600;
const int width = 800;
const float fontSize = (225.0 / 8.0) * ((float) width / height);

void must_init(bool test, const char *description){

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

void updateConstant(float* k, float* r){
  *k += 4.0;
  *r += 4.0;
}

void draw_menu(ALLEGRO_FONT* font){

  float rectXPos1 = width * 0.35;
  float rectXPos2 = 0.3 * width + rectXPos1;

  float rectYSize = fontSize + height * 0.10;
  float rectYPos1 = height * 0.15;
  float rectYPos2 = height * 0.35;
  float rectYPos3 = height * 0.55;
  float rectYPos4 = height * 0.75;

  float k = 4.0;
  float r = 3.0;

  al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(215, 188, 134));
  al_draw_rectangle(width * 0.01, height * 0.01, width * 0.99, height * 0.99, al_map_rgb(0, 0, 0), 5);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rectYPos1 * k / r, ALLEGRO_ALIGN_CENTRE, "NEW GAME");
  al_draw_rectangle(rectXPos1, rectYPos1, rectXPos2, rectYPos1 + rectYSize, al_map_rgb(0, 0, 0), 2);
  updateConstant(&k, &r);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rectYPos2 * k / r, ALLEGRO_ALIGN_CENTRE, "SETTINGS");
  al_draw_rectangle(rectXPos1, rectYPos2, rectXPos2, rectYPos2 + rectYSize, al_map_rgb(0, 0, 0), 2); 
  updateConstant(&k, &r);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rectYPos3 * k / r, ALLEGRO_ALIGN_CENTRE, "HELP");
  al_draw_rectangle(rectXPos1, rectYPos3, rectXPos2, rectYPos3 + rectYSize, al_map_rgb(0, 0, 0), 2);  
  updateConstant(&k, &r);

  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rectYPos4 * k / r, ALLEGRO_ALIGN_CENTRE, "QUIT");
  al_draw_rectangle(rectXPos1, rectYPos4, rectXPos2, rectYPos4 + rectYSize, al_map_rgb(0, 0, 0), 2);  

}

void game_background(){

  must_init(al_init_image_addon(), "image addon");
  ALLEGRO_BITMAP* background = al_load_bitmap("background.jpg");
  must_init(background, "background");
  al_draw_bitmap(background, 0, 0, 0);
  al_destroy_bitmap(background); 

}

void event_register(ALLEGRO_EVENT_QUEUE* queue,  ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer){

  al_register_event_source(queue, al_get_mouse_event_source());
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));

}

void menu(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_KEYBOARD_STATE keyboard,
          bool* game, bool* redraw, ALLEGRO_FONT* font){

  al_wait_for_event(queue, &event);
  switch (event.type){

    case ALLEGRO_EVENT_TIMER:
      *redraw = true;
      break;

    case ALLEGRO_EVENT_KEY_DOWN:
      al_get_keyboard_state(&keyboard);
      if(al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE))
        *game = false;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      *game = false;
      break;

    case ALLEGRO_EVENT_MOUSE_AXES:
      al_draw_filled_rectangle(0, 0, 500, 500, al_map_rgb(100, 6, 34));
      break;  
   }

  if(*redraw && al_is_event_queue_empty(queue)){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    draw_menu(font);
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

  ALLEGRO_FONT* font = al_load_font("font.ttf", fontSize, 0);
  must_init(font, "font");

  /*
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);*/

  event_register(queue, display, timer);

  bool game = true, redraw = true;
  int screen = 1;
  ALLEGRO_EVENT event;
  ALLEGRO_KEYBOARD_STATE keyboard;

  al_start_timer(timer);

  while(game){

    switch(screen){

      case 1:

        menu(event, queue, keyboard, &game, &redraw, font);
        break;

      case 2: 
        break;  

      }  
  }

   al_destroy_font(font);
   al_destroy_display(display);
   al_destroy_timer(timer);
   al_destroy_event_queue(queue);

  return 0;
}
