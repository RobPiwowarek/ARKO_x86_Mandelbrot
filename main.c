#include "paint.h"

int main() 
{
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_DISPLAY *display;
    
    int width = 1000;
    int height = 1000;
    
    double x = -2.0;
    double y = -2.0;
    
    double delta = 4.0/width;
    
    if(!al_init())
    {
        fprintf(stderr, "al_init() error\n");
        return 1;
    }
    
    al_set_app_name("X86 64 Arko Mandelbrot");
    
    if(!al_install_keyboard())
    {
        fprintf(stderr, "al_install_keyboard() error\n");
        return 1;
    }
    
    if(!al_install_mouse())
    {
        fprintf(stderr, "al_install_mouse() error\n");
        return 1;
    }
    
    bitmap = al_create_bitmap(width, height);
    
    if (!bitmap)
    {
        fprintf(stderr, "Bitmap initialization error");
        return 1;
    }
    
    eventQueue = al_create_event_queue();
    
    if (!eventQueue)
    {
        fprintf(stderr, "Event queue creation error");
        al_destroy_bitmap(bitmap);
        return 1;
    }
    
    display = al_create_display(width, height);
    
    if (!display)
    {
        fprintf(stderr, "Display creation error");
        al_destroy_event_queue(eventQueue);
        al_destroy_bitmap(bitmap);
        return 1;
    }
    
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    
    al_register_event_source(eventQueue, al_get_mouse_event_source());
   
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    
    al_set_target_bitmap(al_get_backbuffer(display));
    
    paint(bitmap, width, height, x, y, delta);

    while(1)
    {
        ALLEGRO_EVENT event;
        
        al_wait_for_event(eventQueue, &event);
        
        if ((event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            al_destroy_event_queue(eventQueue);
            al_destroy_bitmap(bitmap);
            al_destroy_display(display);
            return 0;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            x = -2.0;
            y = -2.0;
            delta = 4.0/width;
            paint (bitmap, width, height, x, y, delta);
            printf("x: <%f, %f> y: <%f, %f>\n", x, x + delta * width, y, y + delta * height);
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            ALLEGRO_MOUSE_STATE state;
            
            al_get_mouse_state(&state);
            
            if (state.buttons & 1)
            {
                x += event.mouse.x * delta;
                y += (height - event.mouse.y) * delta;
                delta = delta / 2.0;
                x -= delta * width / 2.0;
                y -= delta * height / 2.0;
                paint (bitmap, width, height, x, y, delta);
                printf("mouse x: %f mouse y: %f \n", event.mouse.x*delta*2, event.mouse.y*delta*2);
                printf("x: <%f, %f> y: <%f, %f>\n", x, x + delta * width, y, y + delta * height);
            }
            else if (state.buttons & 2)
            {
                x -= delta * width / 2.0;
                y -= delta * height / 2.0;
                delta *= 2;
                paint (bitmap, width, height, x, y, delta);  
                printf("x: <%f, %f> y: <%f, %f>\n", x, x + delta * width, y, y + delta * height);
            }
        }
    }
}
