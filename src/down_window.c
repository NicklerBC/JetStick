#include "down_window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static Layer *graphiczone;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // graphiczone
  graphiczone = layer_create(GRect(0, 0, 144, 152));
  layer_add_child(window_get_root_layer(s_window), (Layer *)graphiczone);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  layer_destroy(graphiczone);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void update_graphic_layer(Layer *me, GContext* ctx){
   graphics_draw_line(ctx, GPoint(1,1), GPoint(1,150));
   graphics_draw_line(ctx, GPoint(1,150), GPoint(143,150));
}


void show_down_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  layer_set_update_proc(graphiczone, update_graphic_layer);
  window_stack_push(s_window, true);
}

void hide_down_window(void) {
  window_stack_remove(s_window, true);
}
