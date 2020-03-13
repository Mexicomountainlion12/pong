#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 800;
//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_W, KEY_S
};
int main()
{
	//set up allegro
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	//set up game screen, event queue, and timer
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 /FPS);
	al_start_timer(timer);
	//position of player
	double xPos = 740;
	double yPos = 200;
	double xPos2 = 10;
	double yPos2 = 200;
	//game variables
	bool key[4] = { false, false, false, false }; //holds key clicks
	bool key2[4] = { false, false, false, false };
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop

	float ball_x = 20;
	float ball_y = 200;

	//ball speed
	float ball_dx = -5.0, ball_dy = 4.0;

	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	while (!doexit)//game loop!
	{
		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP]) {
				yPos -= 4.0;
			}
			if (key[KEY_DOWN]) {
				yPos += 4.0;
			}
			if (key2[KEY_UP]) {
				yPos2 -= 4.0;
			}
			if (key2[KEY_DOWN]) {
				yPos2 += 4.0;
			}
			if (ball_x < 0 || ball_x > 800) { //bounces against side walls
				ball_dx = -ball_dx;
			}
			if (ball_y < 0 || ball_y > 800) { //bounce against top and bottom walls
				ball_dy = -ball_dy;
			}
			//MOVE
			ball_x += ball_dx;
			ball_y += ball_dy;

			redraw = true;
		}
		//lets you close with the x button
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
			case ALLEGRO_KEY_W:
				key2[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_S:
				key2[KEY_DOWN] = true;
				break;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_W:
				key2[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_S:
				key2[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}
		//lets you close with the x button
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing (without this things smear)
			al_draw_filled_circle(ball_x, ball_y, 20, al_map_rgb(200, 200, 100));
			al_draw_filled_rectangle(xPos, yPos, xPos + 50, yPos + 400, al_map_rgb(150, 100, 20)); //draw the player
			al_draw_filled_rectangle(xPos2, yPos2, xPos2 + 50, yPos2 + 400, al_map_rgb(150, 100, 20));
			al_flip_display(); //flip everything from memory to gamescreen
		}//end render

	}//end game loop
	//clean up memory
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}