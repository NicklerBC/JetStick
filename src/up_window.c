#include "up_window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18;
static TextLayer *Xaxis;
static TextLayer *Yaxis;
static TextLayer *Zaxis;
static TextLayer *Title;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  // Xaxis
  Xaxis = text_layer_create(GRect(0, 25, 144, 25));
  text_layer_set_text(Xaxis, "Text layer");
  text_layer_set_text_alignment(Xaxis, GTextAlignmentCenter);
  text_layer_set_font(Xaxis, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Xaxis);
  
  // Yaxis
  Yaxis = text_layer_create(GRect(0, 50, 144, 25));
  text_layer_set_text(Yaxis, "Text layer");
  text_layer_set_text_alignment(Yaxis, GTextAlignmentCenter);
  text_layer_set_font(Yaxis, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Yaxis);
  
  // Zaxis
  Zaxis = text_layer_create(GRect(0, 75, 144, 25));
  text_layer_set_text(Zaxis, "Text layer");
  text_layer_set_text_alignment(Zaxis, GTextAlignmentCenter);
  text_layer_set_font(Zaxis, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Zaxis);
  
  // Title
  Title = text_layer_create(GRect(0, 0, 144, 25));
  text_layer_set_text(Title, "Sensors Stuff");
  text_layer_set_text_alignment(Title, GTextAlignmentCenter);
  text_layer_set_font(Title, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)Title);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(Xaxis);
  text_layer_destroy(Yaxis);
  text_layer_destroy(Zaxis);
  text_layer_destroy(Title);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  window_stack_remove(s_window, true);
}

static void click_config_provider(void *context) {
  //window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  //window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void data_handler(AccelData *data, uint32_t num_samples) {
  // Long lived buffer
  static char x_buffer[128];
  static char y_buffer[128];
  static char z_buffer[128];

  // Compose string of all data for 3 samples
  snprintf(x_buffer, sizeof(x_buffer), 
    "%d,%d,%d", 
    data[0].x, data[1].x, data[2].x
  );
  // Compose string of all data for 3 samples
  snprintf(y_buffer, sizeof(y_buffer), 
    "%d,%d,%d", 
    data[0].y, data[1].y, data[2].y
  );
  // Compose string of all data for 3 samples
  snprintf(z_buffer, sizeof(z_buffer), 
    "%d,%d,%d", 
    data[0].z, data[1].z, data[2].z
  );

  //Show the data
  text_layer_set_text(Xaxis, x_buffer);
  text_layer_set_text(Yaxis, y_buffer);
  text_layer_set_text(Zaxis, z_buffer);
}

void show_up_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_set_click_config_provider(s_window, click_config_provider);
  accel_service_set_sampling_rate(ACCEL_SAMPLING_10HZ);
  uint32_t num_samples = 3;
  accel_data_service_subscribe(num_samples, data_handler);
  window_stack_push(s_window, true);
}

void hide_up_window(void) {
  window_stack_remove(s_window, true);
}
