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
               float rect_y_pos1, float rect_y_pos2, float rect_y_pos3,
               ALLEGRO_COLOR button_colors[]){

  float k = 4.0;
  float r = 3.0;

  al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(215, 188, 134));
  al_draw_rectangle(width * 0.01, height * 0.01, width * 0.99, height * 0.99, al_map_rgb(0,0,0), 5);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos1, rect_x_pos2, rect_y_pos1 + rect_y_size, button_colors[0]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos1 * k / r, ALLEGRO_ALIGN_CENTRE, "NOVO JOGO");
  al_draw_rectangle(rect_x_pos1, rect_y_pos1, rect_x_pos2, rect_y_pos1 + rect_y_size, al_map_rgb(0,0,0), 2);
  updateConstant(&k, &r, 5.0);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos2, rect_x_pos2, rect_y_pos2 + rect_y_size, button_colors[1]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos2 * k / r, ALLEGRO_ALIGN_CENTRE, "AJUDA");
  al_draw_rectangle(rect_x_pos1, rect_y_pos2, rect_x_pos2, rect_y_pos2 + rect_y_size, al_map_rgb(0,0,0), 2);  
  updateConstant(&k, &r, 5.0);

  al_draw_filled_rectangle(rect_x_pos1, rect_y_pos3, rect_x_pos2, rect_y_pos3 + rect_y_size, button_colors[2]);
  al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * width, rect_y_pos3 * k / r, ALLEGRO_ALIGN_CENTRE, "SAIR");
  al_draw_rectangle(rect_x_pos1, rect_y_pos3, rect_x_pos2, rect_y_pos3 + rect_y_size, al_map_rgb(0,0,0), 2);  

}

void menu(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font,
          bool* game, bool* redraw, int* screen, ALLEGRO_COLOR button_colors[]){

  float rect_x_pos1 = width * 0.35;
  float rect_x_pos2 = 0.3 * width + rect_x_pos1;
  float rect_y_size = font_size + height * 0.10;
  float rect_y_pos1 = height * 0.15;
  float rect_y_pos2 = height * 0.40;
  float rect_y_pos3 = height * 0.65;

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
          *game = 0;            

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
      break; 
        
   }

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 0){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    draw_menu(font, rect_x_pos1, rect_x_pos2, rect_y_size, rect_y_pos1,
              rect_y_pos2, rect_y_pos3, button_colors);
    al_flip_display();

    *redraw = false;
  }

}

void draw_help(ALLEGRO_FONT* font, float backbutton_x_1, float backbutton_x_2, float backbutton_y_1, float backbutton_y_2, ALLEGRO_COLOR button_colors[]){

  al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(215, 188, 134));
  al_draw_rectangle(width * 0.01, height * 0.01, width * 0.99, height * 0.99, al_map_rgb(0,0,0), 5);

  al_draw_filled_rectangle(backbutton_x_1, backbutton_y_1, backbutton_x_2, backbutton_y_2, button_colors[7]);  
  al_draw_rectangle(backbutton_x_1, backbutton_y_1, backbutton_x_2, backbutton_y_2, al_map_rgb(0, 0, 0), 2);
  al_draw_filled_rectangle(backbutton_x_1 + width * 0.02, backbutton_y_1 + 0.02 * height,
                           backbutton_x_2 - width * 0.01, backbutton_y_2 - height * 0.02, al_map_rgb(0, 0, 0));
  al_draw_filled_triangle(backbutton_x_1 + width * 0.005, backbutton_y_1 + height * 0.025,
                          backbutton_x_1 + width * 0.02, backbutton_y_1 + height * 0.01,
                          backbutton_x_1 + width * 0.02, backbutton_y_2 - height * 0.01,
                          al_map_rgb(0, 0, 0));

  al_draw_filled_rectangle(width * 0.10, height * 0.15, width * 0.90, height * 0.85, al_map_rgb(255, 255, 255));
  al_draw_rectangle(width * 0.10, height * 0.15, width * 0.90, height * 0.85, al_map_rgb(0, 0, 0), 1);

  const char * text = "JOGABILIDADE: o personagem central deve capturar seus aliados que possuem cor azul para aumentar de tamanho, "
                      "enquanto precisa defender-se de seus inimigos que estão em vermelho, para isso utilizando seu escudo ou atirando com o canhão.\n\n"
                      "OBJETIVO: atingir o tamanho de seu escudo antes de perder todas suas vidas.\n\n"
                      "CANHÃO: o player pode atirar a cada 1 segundo, entretanto não pode haver mais que um tiro na tela.\n\n"
                      "MÍSSIL: cada vez que o player atingir 50 pontos será dado um tiro especial, o qual some quando atingir a parede 5 vezes"
                      " ou colidir com 3 inimigos. Será sinalizado com a mudança de cor do canhão quando essa habilidade estiver disponível. Se o aliado for atingido"
                      ", todas os inimigos diminuirão em 25 por cento sua velocidade por 5 segundos.\n\n"
                      "ARMADURA: a armadura é habilitada a cada nível múltiplo de 3 quando o player pressionar a tecla espaço. E será notificado com um "
                      "símbolo de escudo na parte superior da tela. Quando ativada, a habilidade durará de 5 a 10 segundos. A partir do momento em que"
                      " a tecla espaço for soltada, a armadura retrairá e não será possível utilizá-la até a próxima fase múltipla de 3. "
                      "No momento que estiver ativa, protegerá contra todas as entidades que a encostarem, porém o player diminuirá de tamanho constantemente."
                      " Também só poderá ser acionada se o player tiver um mínimo de tamanho, e uma vez que chegue ao limite enquanto acionada a armadura,"
                      " ela sumirá automaticamente.\n\n"
                      "PAUSE: o jogador poderá pausar o jogo uma vez a cada fase, e essa opção torna-se possível sempre que aumentar de nível.\n\n"
                      "PONTOS: cada inimigo destruído pelo escudo = 1 ponto, pelo canhão = 2 pontos, pela armadura = 3 pontos e pelo míssil = 5 pontos.\n\n"
                      "NÍVEIS: o próximo nível sempre precisará de mais pontos que o anterior, sendo mostrado na tela quantos pontos necessários para atingí-lo.\n\n";

  al_draw_multiline_text(font, al_map_rgb(0, 0, 0), width * 0.105, height * 0.17, width * 0.79, 0.02 * height, ALLEGRO_ALIGN_LEFT, text);

}

void help(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_KEYBOARD_STATE keyboard,
                    ALLEGRO_FONT* font, ALLEGRO_TIMER* timer, bool* game, bool* redraw, int* screen,
                    ALLEGRO_COLOR button_colors[], float backbutton_x_1, float backbutton_x_2, float backbutton_y_1, float backbutton_y_2){

  switch (event.type){

    case ALLEGRO_EVENT_TIMER:
      *redraw = true;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      *game = false;
      break;

    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      if(event.mouse.x >= backbutton_x_1 && event.mouse.x <= backbutton_x_2
         && event.mouse.y >= backbutton_y_1 && event.mouse.y <= backbutton_y_2)
        *screen = 0;      
      break;

    case ALLEGRO_EVENT_MOUSE_AXES:
      if(event.mouse.x >= backbutton_x_1 && event.mouse.x <= backbutton_x_2
         && event.mouse.y >= backbutton_y_1 && event.mouse.y <= backbutton_y_2)
        update_color(button_colors, 7, true);
      else update_color(button_colors, 7, false);      
      break;  
  
   }

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 3){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    draw_help(font, backbutton_x_1, backbutton_x_2, backbutton_y_1, backbutton_y_2, button_colors);
    al_flip_display();

    *redraw = false;
  } 

}

void draw_difficulty(ALLEGRO_FONT* font, float rect_x_pos1, float rect_x_pos2, float rect_y_size,
                     float rect_y_pos1, float rect_y_pos2, float rect_y_pos3, ALLEGRO_COLOR button_colors[],
                     float backbutton_x_1, float backbutton_x_2, float backbutton_y_1, float backbutton_y_2){

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

  al_draw_filled_rectangle(backbutton_x_1, backbutton_y_1, backbutton_x_2, backbutton_y_2, button_colors[7]);
  al_draw_rectangle(backbutton_x_1, backbutton_y_1, backbutton_x_2, backbutton_y_2, al_map_rgb(0, 0, 0), 2);
  al_draw_filled_rectangle(backbutton_x_1 + width * 0.02, backbutton_y_1 + 0.02 * height,
                           backbutton_x_2 - width * 0.01, backbutton_y_2 - height * 0.02, al_map_rgb(0, 0, 0));
  al_draw_filled_triangle(backbutton_x_1 + width * 0.005, backbutton_y_1 + height * 0.025,
                          backbutton_x_1 + width * 0.02, backbutton_y_1 + height * 0.01,
                          backbutton_x_1 + width * 0.02, backbutton_y_2 - height * 0.01,
                          al_map_rgb(0, 0, 0)); 

}

void set_difficulty(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_KEYBOARD_STATE keyboard,
                    ALLEGRO_FONT* font, ALLEGRO_TIMER* timer, bool* game, bool* redraw, int* screen,
                    int* difficulty, ALLEGRO_COLOR button_colors[], float backbutton_x_1, float backbutton_x_2, float backbutton_y_1, float backbutton_y_2){

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

      if(event.mouse.x >= backbutton_x_1 && event.mouse.x <= backbutton_x_2
         && event.mouse.y >= backbutton_y_1 && event.mouse.y <= backbutton_y_2)
        *screen = 0;  

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
      if(event.mouse.x >= backbutton_x_1 && event.mouse.x <= backbutton_x_2
         && event.mouse.y >= backbutton_y_1 && event.mouse.y <= backbutton_y_2)
        update_color(button_colors, 7, true);
      else update_color(button_colors, 7, false);                 
      break;     
   }

  *screen = *difficulty == 0 ? *screen : 2; 
  if(*screen == 2) al_set_timer_count(timer, 0);

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 1){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    draw_difficulty(font, rect_x_pos1, rect_x_pos2,
                    rect_y_size, rect_y_pos1,
                    rect_y_pos2, rect_y_pos3, button_colors,
                    backbutton_x_1, backbutton_x_2, backbutton_y_1, backbutton_y_2);
    al_flip_display();

    *redraw = false;
  } 

}

void victory(ALLEGRO_FONT* font){

  al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(215, 188, 134));
  al_draw_rectangle(width * 0.01, height * 0.01, width * 0.99, height * 0.99, al_map_rgb(0, 0, 0), 5);

}

void game_over(){

  al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(215, 188, 134));
  al_draw_rectangle(width * 0.01, height * 0.01, width * 0.99, height * 0.99, al_map_rgb(0, 0, 0), 5);

}

void level_logic(int* level, int player_points, int* player_life, bool* increasing_life, bool* level_updated){

  int criteria = 50 + *level * 10;

  int level_update_check = *level;

  *level += floor((player_points) / criteria) >= *level ? 1 : 0;

  *level_updated = level_update_check != *level;

  if(*level % 2 == 0 && *level % 10 != 0)
    *increasing_life = true;

  if(*level % 10 == 0 && *increasing_life){

    (*player_life)++;
    *increasing_life = false;

  }

}

void armor_logic(ALLEGRO_TIMER* timer, bool* armor, float* player_radius, float* delay_armor, float* random_seconds_5_10){

  if(*delay_armor == 0){

    *delay_armor = ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10);
    *random_seconds_5_10 = (float) (rand() % 6 + 5);

  }

  *armor = true;

  if(*player_radius > width / height * 10 && *delay_armor + *random_seconds_5_10 > ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10)){

    (*player_radius) -= 0.008;

  }else{
  
    *armor = false;

  }

}

struct shot_properties{

  int radius;

  float pos_x;
  float pos_y;

  float x_velocity;
  float y_velocity;

  int direction_x;
  int direction_y;

  ALLEGRO_COLOR color;
  bool alive;

  bool missile;
  int missile_resistance_edges;
  int missile_resistance_enemies;

};

void shots_colision(struct shot_properties* shot){

  bool x_edge_hitted = shot->pos_x > width || shot->pos_x < 0;

  bool y_edge_hitted = shot->pos_y > height || shot->pos_y < 0;

  if(x_edge_hitted || y_edge_hitted){ 

    if(shot->missile && shot->missile_resistance_edges > 0){
      
      shot->missile_resistance_edges--;
      
      if(x_edge_hitted) shot->direction_x = -shot->direction_x;     
       

      if(y_edge_hitted) shot->direction_y = -shot->direction_y;
        

    }else shot->alive = false;

  }      

}

void shots_generation(struct shot_properties* shot, float* shield, float gun_size, float* player_radius, bool missile){

  shot->radius = 5;

  shot->pos_x = (*player_radius + gun_size) * (-cos(*shield + M_PI / 2)) + half_width;
  shot->pos_y = (*player_radius + gun_size) * (-sin(*shield + M_PI / 2)) + half_height;
  
  shot->x_velocity = shot->pos_x - half_width;
  shot->y_velocity = shot->pos_y - half_height;

  shot->color = al_map_rgb(255, 0, 0);
  shot->alive = true;

  shot->missile = missile;

  shot->missile_resistance_edges = shot->missile ? 4 : 0;
  shot->missile_resistance_enemies = shot->missile ? 2 : 0;

  shot->direction_x = 1;
  shot->direction_y = 1;

}

void shots_movement(struct shot_properties* shot){

  float speed = 0.2;

  shot->pos_x += shot->x_velocity * speed * shot->direction_x;
  shot->pos_y += shot->y_velocity * speed * shot->direction_y;

}

void gun_logic(ALLEGRO_TIMER* timer, bool shot_fired, struct shot_properties* shot, float* shield, float gun_size,
               float* player_radius, float* delay_1s, int player_points, bool* missile, int* missile_update){

  int previous_missile_update = *missile_update;
  *missile_update += (int) floor(player_points / 50) >= *missile_update ? 1 : 0;

  if(*missile_update > previous_missile_update)
    *missile = true;

  if(shot_fired && !shot->alive && *delay_1s == 0){

    shots_generation(shot, shield, gun_size, player_radius, *missile);
    *delay_1s = ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10);        

  }

  if(*delay_1s + 1 <= ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10)) 
    *delay_1s = 0;

  shots_movement(shot);
  shots_colision(shot);

  if(shot->alive) al_draw_filled_circle(shot->pos_x, shot->pos_y,
                                        shot->radius, shot->color);

  if(*missile && shot->alive) *missile = false;  

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

void enemy_generation(struct enemy enemies[], int* index_enemies, int* max_enemies, int level, int difficulty){

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

    float angle_direction_x = (float)(rand() % 20) - 10;
    float angle_direction_y = (float)(rand() % 20) - 10;

    float speed_max = 3 * difficulty + 10 + level;
    float speed_min = 3 * difficulty + 2 + level;

    float speed = (float)((rand() % (int) (speed_max - speed_min)) + speed_min) / 3000;

    float x_velocity = axes[0] ? abs(enemies[*index_enemies].pos_x - half_width + angle_direction_x) * speed :
                                 -abs(enemies[*index_enemies].pos_x - half_width + angle_direction_x) * speed ;

    float y_velocity = axes[1] ? abs(enemies[*index_enemies].pos_y - half_height + angle_direction_y) * speed :
                                 -abs(enemies[*index_enemies].pos_y - half_height + angle_direction_y) * speed;

    enemies[*index_enemies].vel_pos_x = x_velocity;
    enemies[*index_enemies].vel_pos_y = y_velocity;

    enemies[*index_enemies].radius = rand() % 5 + 3;

    enemies[*index_enemies].alive = true;

    *index_enemies += *index_enemies < *max_enemies - 1 ? 1 : - *max_enemies - 1;

    int probability_ally = 10;

    enemies[*index_enemies].ally = rand() % probability_ally == 0;

    enemies[*index_enemies].color = enemies[*index_enemies].ally ? al_map_rgb(0, 204, 204) : al_map_rgb(129, 0, 0);

  }

}

void movement_update(struct enemy enemies[], int i, bool ally_hitted_missile){

  float decrease = ally_hitted_missile ? 0.25 : 1;
  enemies[i].pos_x += enemies[i].vel_pos_x * decrease;
  enemies[i].pos_y += enemies[i].vel_pos_y * decrease;

}

void colision_check(struct enemy enemies[], int i, float* shield, float* player_radius, float player_shield_radius,
                    struct shot_properties* shot, int* player_points, bool armor, float shrinking_armor, bool armor_started, bool* ally_hitted_missile){

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

  if((armor || armor_started) && pow(half_width - enemies[i].pos_x, 2) + pow(half_height - enemies[i].pos_y, 2) <=
     pow(width / height * 60 + enemies[i].radius - shrinking_armor, 2)) shield_hitted = true;                       

  float enemy_area = M_PI * pow(enemies[i].radius, 2);
  float player_area = M_PI * pow(*player_radius, 2);

  float difference = enemies[i].ally ? player_area + enemy_area : player_area - enemy_area;                       
  float radius_change = difference > 0 ? sqrt(difference / M_PI) : 0;

  if(player_hitted) *player_radius = radius_change;

  if(shield_hitted && !enemies[i].ally)
    if(armor)
      (*player_points) += 3;
    else
      (*player_points)++;

  if((player_hitted || edge_hitted || shield_hitted))
    enemies[i].alive = false;

  if(shot->alive){

    float distance = sqrt(pow(shot->pos_x - (enemies[i].pos_x), 2) +
                          pow(shot->pos_y - (enemies[i].pos_y), 2));

    if(distance <= shot->radius + enemies[i].radius){

      if(shot->missile){

        if(shot->missile_resistance_enemies > 0) shot->missile_resistance_enemies--;
        else shot->alive = false;

        if(enemies[i].ally){

          *ally_hitted_missile = true;

        }else{

          *player_points += 5;
          *player_radius += *player_radius * 0.02;

        }

        enemies[i].alive = false;

      }else{

        shot->alive = false;

        if(!enemies[i].ally){

          enemies[i].alive = false;
          *player_radius += *player_radius * 0.02;
          *player_points += 2;

        }

      }

    }

  }

}

void enemy_logic(ALLEGRO_TIMER* timer, struct enemy enemies[], int* index_enemies,
                 int* max_enemies, float* mouse_pos_x, float* mouse_pos_y, float* shield,
                 float* player_radius, float player_shield_radius, struct shot_properties* shot,
                 int* player_points, bool armor, float shrinking_armor, bool armor_started, int level, int difficulty, bool* ally_hitted_missile,
                 float* delay_5s){

  int spawn_rate =  level >= 49 ? 2 : (50 - level);
  if(rand() % spawn_rate == 0) enemy_generation(enemies, index_enemies, max_enemies, level, difficulty);

  for(int i = 0; i < *max_enemies; i++){
 
    if(enemies[i].alive){

      movement_update(enemies, i, *ally_hitted_missile); 
      colision_check(enemies, i, shield, player_radius, player_shield_radius,
                     shot, player_points, armor, shrinking_armor, armor_started, ally_hitted_missile);

      al_draw_filled_circle(enemies[i].pos_x, enemies[i].pos_y,
                            enemies[i].radius, enemies[i].color);
      }

  }

  if(*ally_hitted_missile && *delay_5s == 0)
    *delay_5s = ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10);

  if(*delay_5s + 5 <= ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10) && *ally_hitted_missile){

    *ally_hitted_missile = false;
    *delay_5s = 0;

  }
  
}

void game_background(ALLEGRO_FONT* font, ALLEGRO_TIMER* timer, float player_radius, float player_shield_radius, float* shield,
                     float* mouse_pos_x, float* mouse_pos_y, float gun_size, int* player_life, int* player_points, bool armor,
                     bool armor_available, float delay_armor, float random_seconds_5_10, bool* armor_started, float* shrinking_armor,
                     int level, int levels_change[], bool level_updated, int* duration_level_up, bool missile, bool shot_fired){

  *shield = M_PI / 2 + atan(*mouse_pos_y / *mouse_pos_x);
  *shield += *mouse_pos_x >= 0 ? M_PI : 0;

  float player_shield_armor = player_shield_radius - *shrinking_armor;

  float gun_point_1_x = (player_radius + gun_size) * (-cos(*shield + M_PI / 2)) + half_width;
  float gun_point_1_y = (player_radius + gun_size) * (-sin(*shield + M_PI / 2)) + half_height;

  float gun_point_2_x = player_radius * (-cos(*shield + 5 + M_PI / 2)) + half_width;
  float gun_point_2_y = player_radius * (-sin(*shield + 5 + M_PI / 2)) + half_height;

  float gun_point_3_x = player_radius * (-cos(*shield - 5 + M_PI / 2)) + half_width;
  float gun_point_3_y = player_radius * (-sin(*shield - 5 + M_PI / 2)) + half_height;

  int criteria = 50 + level * 10;
  levels_change[level] = criteria + levels_change[level - 1] + 10 * (level - 1);

  ALLEGRO_COLOR gun_color = missile && !shot_fired ? al_map_rgb(0, 255, 255) : al_map_rgb(0, 123, 123);

  must_init(al_init_image_addon(), "image addon");
  ALLEGRO_BITMAP* background = al_load_bitmap("background.png");
  must_init(background, "background");
  al_draw_bitmap(background, 0, 0, 0); 

  if(armor) al_draw_filled_circle(half_width, half_height, player_shield_radius, al_map_rgba(0, 0, 0, 100));
  else if(*armor_started && player_radius) al_draw_filled_circle(half_width, half_height, player_shield_armor, al_map_rgba(0, 0, 0, 100));

  al_draw_filled_circle(half_width, half_height, player_radius, al_map_rgb(0, 0, 0));
  al_draw_circle(half_width, half_height, player_radius, al_map_rgb(0, 123, 123), 3);
  al_draw_arc(half_width, half_height, player_shield_radius, *shield, M_PI, 
              al_map_rgb(0, 0, 0), 3);
  al_draw_filled_triangle(gun_point_1_x, gun_point_1_y, gun_point_2_x, gun_point_2_y,
                          gun_point_3_x, gun_point_3_y, al_map_rgb(0, 0, 0));
  al_draw_triangle(gun_point_1_x, gun_point_1_y, gun_point_2_x, gun_point_2_y,
                          gun_point_3_x, gun_point_3_y, gun_color, 3);

  al_draw_filled_rectangle(0, 0, width, height * 0.05, al_map_rgb(0, 0, 0));
  al_draw_rectangle(0, 0, width, height * 0.05, al_map_rgb(204, 102, 0), 3);

  al_draw_textf(font, al_map_rgb(255, 255, 255), width * 0.01, 0, ALLEGRO_ALIGN_LEFT,
                "Tempo: %.2f", ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10));

  al_draw_textf(font, al_map_rgb(255, 255, 255), width * 0.25, 0, ALLEGRO_ALIGN_LEFT, "Vidas restantes: %d", *player_life);

  al_draw_textf(font, al_map_rgb(255, 255, 255), width * 0.5, 0, ALLEGRO_ALIGN_CENTRE, "%d pts", *player_points);

  al_draw_textf(font, al_map_rgb(255, 255, 255), width * 0.99, 0, ALLEGRO_ALIGN_RIGHT, "(Próximo %d pts) Nível: %d", levels_change[level], level);

  al_draw_textf(font, al_map_rgb(255, 255, 255), width * 0.70, 0, ALLEGRO_ALIGN_RIGHT, "Pause: %f", player_radius);

  if(armor_available){

    al_draw_elliptical_arc(width * 0.16, 0.01 * height, height * 0.02, height * 0.03, 0, M_PI, al_map_rgb(255, 204, 0), 6);
    al_draw_filled_rectangle(width * 0.16 - 0.02 * height, height * 0.01, width * 0.16 + 0.02 * height, height * 0.01 + height *0.01, al_map_rgb(255, 204, 0));

    al_draw_elliptical_arc(width * 0.16, 0.015 * height, height * 0.01, height * 0.02, 0, M_PI, al_map_rgb(255, 255, 255), 6);
    al_draw_filled_rectangle(width * 0.16 - 0.01 * height, height * 0.015, width * 0.16 + 0.01 * height, height * 0.02 + height *0.015, al_map_rgb(255, 255, 255));

    if(armor || (delay_armor + random_seconds_5_10 > ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10) && delay_armor != 0)){

      al_draw_textf(font, al_map_rgb(255, 204, 0), width * 0.17 + height * 0.03, 0, ALLEGRO_ALIGN_LEFT, "%.2f",
                    random_seconds_5_10 + delay_armor - ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10));
      *armor_started = true;

    }

  }

  if(*armor_started && (delay_armor + random_seconds_5_10 < ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10))
                        || player_radius < width / height * 10)
    *shrinking_armor += 0.1;

  if(player_shield_radius - *shrinking_armor < player_radius){

    *shrinking_armor = 0;
    *armor_started = false;

  }

  if(level_updated)
    *duration_level_up = ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10);

  if(*duration_level_up + 2 > ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10) && level != 1)
    al_draw_text(font, al_map_rgb(102, 204, 255), half_width, height * 0.3, ALLEGRO_ALIGN_CENTRE, "LEVEL UP");
  else *duration_level_up = 0;

  al_destroy_bitmap(background);

}

void play_game(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_KEYBOARD_STATE keyboard,
               ALLEGRO_FONT* font, ALLEGRO_TIMER* timer, bool* game, bool* redraw, int* screen,
               float* player_radius, float player_shield_radius, float* shield, float* mouse_pos_x, 
               float* mouse_pos_y, struct enemy enemies[], int* index_enemies, int* max_enemies,
               float gun_size, float* delay_1s, struct shot_properties* shot, int* player_life,
               int* player_points, int* level, int levels_change[], bool* level_updated, int* duration_level_up, int difficulty,
               float* delay_armor, float* random_seconds_5_10, bool* armor_first_use, bool* armor_started, float* shrinking_armor,
               bool* increasing_life, bool* missile,
               int* missile_update, bool* ally_hitted_missile, float* delay_5s, bool* pause_available, bool* pause){

  bool shot_fired = false;
  bool armor = false;

  al_get_keyboard_state(&keyboard);

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

    case ALLEGRO_EVENT_KEY_DOWN:
      if(al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE) && *pause_available){
        al_stop_timer(timer);
        *pause = true;
      }
      break;  

  }

  if(*level_updated){
   
    *delay_armor = 0;
    *pause_available = true;

  }
    
  if(*level % 3 == 0 && al_key_down(&keyboard, ALLEGRO_KEY_SPACE) && *player_radius > width / height * 10 && *delay_armor >= 0){

      armor_logic(timer, &armor, player_radius, delay_armor, random_seconds_5_10);
      *armor_first_use = true;

  }else if(*armor_first_use){

    *delay_armor = -10;
    *armor_first_use = false;

  }

  bool armor_available = armor || (*level % 3 == 0 && *delay_armor == 0) ||
                         (*delay_armor + *random_seconds_5_10 > ALLEGRO_MSECS_TO_SECS(al_get_timer_count(timer) * 10)
                           && *delay_armor != 0 && *armor_first_use);

  if(al_key_down(&keyboard, ALLEGRO_KEY_Z))
    *player_points += 1;

  if(*redraw && al_is_event_queue_empty(queue) && *screen == 2){

    al_clear_to_color(al_map_rgb(0, 0, 100));
    game_background(font, timer, *player_radius, player_shield_radius, shield,
                    mouse_pos_x, mouse_pos_y, gun_size, player_life, player_points,
                    armor, armor_available, *delay_armor, *random_seconds_5_10, armor_started, shrinking_armor,
                    *level, levels_change, *level_updated, duration_level_up, *missile,
                    shot_fired);
    enemy_logic(timer, enemies, index_enemies, max_enemies,
                mouse_pos_x, mouse_pos_y, shield, player_radius,
                player_shield_radius, shot, player_points, armor,
                *shrinking_armor, *armor_started, *level, difficulty, ally_hitted_missile, delay_5s);    

    if(*player_radius <= 0 && *player_life > 0){

      *player_radius = width / height * 20;
      (*player_life)--;

    }                            
  
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    if (state.buttons & 1)
      shot_fired = true; 
    
    gun_logic(timer, shot_fired, shot, shield, gun_size, player_radius,
              delay_1s, *player_points, missile, missile_update);

    level_logic(level, *player_points, player_life, increasing_life, level_updated);
    
    al_flip_display();

    *redraw = false;

  }

  if(!*redraw && al_is_event_queue_empty(queue) && *pause) {

    al_draw_filled_rectangle(0.25 * width, 0.25 * height, 0.75 * width, 0.75 * height, al_map_rgb(215, 188, 134));
    al_draw_rectangle(0.25 * width, 0.25 * height, 0.75 * width, 0.75 * height, al_map_rgb(0, 0, 0), 3);

    al_draw_text(font, al_map_rgb(0, 0, 0), half_width, height * 0.375, ALLEGRO_ALIGN_CENTRE, "VOLTAR AO JOGO");
    al_draw_text(font, al_map_rgb(0, 0, 0), half_width, height * 0.575, ALLEGRO_ALIGN_CENTRE, "SAIR DO JOGO");
    al_draw_rectangle(0.4 * width, 0.35 * height, 0.6 * width, 0.45 * height, al_map_rgb(0, 0, 0), 2);
    al_draw_rectangle(0.4 * width, 0.55 * height, 0.6 * width, 0.65 * height, al_map_rgb(0, 0, 0), 2);    


    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    if (state.buttons & 1 && *mouse_pos_x > 0.4 * width - half_width &&
        *mouse_pos_x < 0.6 * width - half_width){

      if(*mouse_pos_y > 0.35 * height - half_height && *mouse_pos_y < 0.45 * height - half_height){
        al_resume_timer(timer);
        *pause_available = false;
        *pause = false;
      }

      if(*mouse_pos_y > 0.55 * height - half_height && *mouse_pos_y < 0.65 * height - half_height)
        *game = false;
    }

    al_flip_display();

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

  ALLEGRO_FONT* help_font = al_load_font("help_font.ttf", font_size / 3, 0);
  must_init(help_font, "help_font");

  ALLEGRO_EVENT event;
  ALLEGRO_KEYBOARD_STATE keyboard;

  event_register(queue, display, timer);

  float backbutton_x_1 = width * 0.05;
  float backbutton_x_2 = width * 0.10;
  float backbutton_y_1 = height * 0.05;
  float backbutton_y_2 = height * 0.10;

  bool game = true, redraw = true;
  int screen = 0;
  ALLEGRO_COLOR button_colors[10];
  for(int i = 0; i < 10; i++)
    button_colors[i] = al_map_rgb(215, 188, 134);

  
  float player_shield_radius = width / height * 60;
  float shield = 0;
  float mouse_pos_x = 0;
  float mouse_pos_y = - half_height;

  float player_radius = width / height * 20;
  int player_life = 3;
  int player_points = 0;

  struct shot_properties shot;
  float gun_size = player_radius * 0.8; 
  float delay_1s = 0;
  bool missile = false;
  int missile_update = 1;
  bool ally_hitted_missile = false;
  float delay_5s = 0;

  int max_enemies = 10;
  int index_enemies = 0;
  struct enemy enemies[max_enemies];
  for(int i = 0; i < max_enemies; i++)
    enemies[i].alive = false;

  int level = 1;
  int levels_change[100];
  levels_change[0] = 0;
  bool level_updated = false;
  bool increasing_life = false;
  int duration_level_up = 0;

  float delay_armor = 0;
  float random_seconds_5_10;
  bool armor_started = false;
  float shrinking_armor = 0;
  bool armor_first_use = false;

  bool pause_available = true;
  bool pause = false;

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
                       &difficulty, button_colors, backbutton_x_1, backbutton_x_2, backbutton_y_1, backbutton_y_2);
        break;  

      case 2: 
        
        play_game(event, queue, keyboard, game_font, timer, &game, &redraw,
                  &screen, &player_radius, player_shield_radius, &shield, &mouse_pos_x,
                  &mouse_pos_y, enemies, &index_enemies, &max_enemies, gun_size, &delay_1s,
                  &shot, &player_life, &player_points, &level, levels_change, &level_updated,
                  &duration_level_up, difficulty, &delay_armor, &random_seconds_5_10, &armor_first_use, &armor_started, &shrinking_armor,
                  &increasing_life, &missile, &missile_update, &ally_hitted_missile, &delay_5s, &pause_available, &pause);
        break;

      case 3:

        help(event, queue, keyboard, help_font, timer, &game, &redraw, &screen,
             button_colors, backbutton_x_1, backbutton_x_2, backbutton_y_1, backbutton_y_2);
        break;

      case 4:

        victory(font);
        break;

      case 5:
        
        game_over();
        break;  
    }

  }

  al_destroy_font(font);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;

}
