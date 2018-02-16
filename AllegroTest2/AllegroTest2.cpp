

#include "stdafx.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

int main()
{
	bool arriba = false;
	bool abajo = false;
	bool izquierda = false;
	bool derecha = false;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_BITMAP * bitmap = NULL;

	//Creación de la ventana y de la lista de eventos
	al_init();
	display = al_create_display(800, 600);
	queue = al_create_event_queue();

	al_install_keyboard();
	//al_install_mouse();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	//al_register_event_source(queue, al_get_mouse_event_source());

	al_init_image_addon();

	//Cargar imagen
	bitmap = al_load_bitmap("snake.png");
	assert(bitmap != NULL);

	//X y Y indican la posición de la imágen
	bool running = true;
	float x = 300, y = 200;

	int width = al_get_display_width(display);
	while (running) {
		al_clear_to_color(al_map_rgba_f(0, 0, 0, 1));
		al_draw_bitmap(bitmap, x, y, 0);
		al_flip_display();

		ALLEGRO_EVENT event;

		if (!al_is_event_queue_empty(queue)) {
			al_wait_for_event(queue, &event);
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				running = false;
		}

		// Evaluación activa del teclado
		ALLEGRO_KEYBOARD_STATE keyState;

		//Movimiento de la imágen en las cuatro direcciones
		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
			abajo = false;
			arriba = false;
			izquierda = false;
			derecha = true;
		}
			//x += 0.1;
		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
		{
			abajo = false;
			arriba = false;
			izquierda = true;
			derecha = false;
		}
			//x -= 0.1;
		if (al_key_down(&keyState, ALLEGRO_KEY_UP))
		{
			abajo = false;
			arriba = true;
			izquierda = false;
			derecha = false;
		}
			//y -= 0.1;
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))	
		{
			abajo = true;
			arriba = false;
			izquierda = false;
			derecha = false;
		}
			//y += 0.1;
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
			running = false;
		}

		if (arriba==true) {
			y -= 0.1;
		}
		else if (abajo==true) {
			y += 0.1;
		}
		else if (izquierda==true) {
			x -= 0.1;
		}
		else if (derecha == true) {
			x += 0.1;
		}
	}

	//Destrucción del programa después de que se cierre manualmente
	al_destroy_display(display);
	al_uninstall_keyboard();
	//al_uninstall_mouse();
	al_destroy_bitmap(bitmap);

	system("pause");

    return 0;
}

