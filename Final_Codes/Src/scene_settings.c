// TODO-HACKATHON 3-9: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"
#include "scene_leaderboard.h"
#include "scene_menu_object.h"
// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO-IF: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
Checkbox worm_mode_checkbox;
Checkbox better_BGM_checkbox;
Checkbox key_bind_up_checkbox;
Checkbox key_bind_down_checkbox;
Checkbox key_bind_left_checkbox;
Checkbox key_bind_right_checkbox;
bool key_bind_up = false;
bool key_bind_down = false;
bool key_bind_left = false;
bool key_bind_right = false;
static void init(){
	worm_mode_checkbox = checkbox_create(SCREEN_W/2 - 200, SCREEN_H/2 - 280, 32, 32, "Assets/checkbox_blank.png", "Assets/checkbox_hover.png", "Assets/checkbox_checked.png", &worm_mode);
	better_BGM_checkbox = checkbox_create(SCREEN_W/2 - 200, SCREEN_H/2 - 230, 32, 32, "Assets/checkbox_blank.png", "Assets/checkbox_hover.png", "Assets/checkbox_checked.png", &betterBGM);
	key_bind_up_checkbox = checkbox_create(SCREEN_W/2 - 200, SCREEN_H/2 - 170, 32, 32, "Assets/keybind_default.png", "Assets/keybind_hover.png", "Assets/keybind_pressed.png", &key_bind_up);
	key_bind_down_checkbox = checkbox_create(SCREEN_W/2 - 200, SCREEN_H/2 - 120, 32, 32, "Assets/keybind_default.png", "Assets/keybind_hover.png", "Assets/keybind_pressed.png", &key_bind_down);
	key_bind_left_checkbox = checkbox_create(SCREEN_W/2 - 200, SCREEN_H/2 - 70, 32, 32, "Assets/keybind_default.png", "Assets/keybind_hover.png", "Assets/keybind_pressed.png", &key_bind_left);
	key_bind_right_checkbox = checkbox_create(SCREEN_W/2 - 200, SCREEN_H/2 - 20, 32, 32, "Assets/keybind_default.png", "Assets/keybind_hover.png", "Assets/keybind_pressed.png", &key_bind_right);
}
static void draw(void ){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2,
		SCREEN_H - 150,
		ALLEGRO_ALIGN_CENTER,
		"<ENTER> Back to menu"
	);
	drawCheckbox(worm_mode_checkbox);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2 - 150,
		SCREEN_H/2 - 280,
		0,
		"Worm Mode"
	);
	drawCheckbox(better_BGM_checkbox);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2 - 150,
		SCREEN_H/2 - 230,
		0,
		"Better BGM"
	);
	char output[100];
	sprintf(output, "Key Bind Up: %s", al_keycode_to_name(up_keycode));
	drawCheckbox(key_bind_up_checkbox);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2 - 150,
		SCREEN_H/2 - 170,
		0,
		output
	);
	sprintf(output, "Key Bind Down: %s", al_keycode_to_name(down_keycode));
	drawCheckbox(key_bind_down_checkbox);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2 - 150,
		SCREEN_H/2 - 120,
		0,
		output
	);
	sprintf(output, "Key Bind Left: %s", al_keycode_to_name(left_keycode));
	drawCheckbox(key_bind_left_checkbox);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2 - 150,
		SCREEN_H/2 - 70,
		0,
		output
	);
	sprintf(output, "Key Bind Right: %s", al_keycode_to_name(right_keycode));
	drawCheckbox(key_bind_right_checkbox);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2 - 150,
		SCREEN_H/2 - 20,
		0,
		output
	);
}

static void on_key_down(int keycode) {
	if(key_bind_up){
		up_keycode = keycode;
		key_bind_up = false;
	}else if(key_bind_down){
		down_keycode = keycode;
		key_bind_down = false;
	}else if(key_bind_left){
		left_keycode = keycode;
		key_bind_left = false;
	}else if(key_bind_right){
		right_keycode = keycode;
		key_bind_right = false;
	}else{
		switch (keycode){
			case ALLEGRO_KEY_ENTER:
				game_change_scene(scene_menu_create());
				break;
			default:
				break;
		}
	}
}
static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	worm_mode_checkbox.hovered = checkboxHover(worm_mode_checkbox, mouse_x, mouse_y);
	better_BGM_checkbox.hovered = checkboxHover(better_BGM_checkbox, mouse_x, mouse_y);
	key_bind_up_checkbox.hovered = checkboxHover(key_bind_up_checkbox, mouse_x, mouse_y);
	key_bind_down_checkbox.hovered = checkboxHover(key_bind_down_checkbox, mouse_x, mouse_y);
	key_bind_left_checkbox.hovered = checkboxHover(key_bind_left_checkbox, mouse_x, mouse_y);
	key_bind_right_checkbox.hovered = checkboxHover(key_bind_right_checkbox, mouse_x, mouse_y);
}
static void on_mouse_down(int a, int mouse_x, int mouse_y, int f) {
	if (worm_mode_checkbox.hovered) *worm_mode_checkbox.flag = !(*worm_mode_checkbox.flag);
	if (better_BGM_checkbox.hovered) *better_BGM_checkbox.flag = !(*better_BGM_checkbox.flag);
	if (key_bind_up_checkbox.hovered) *key_bind_up_checkbox.flag = !(*key_bind_up_checkbox.flag);
	if (key_bind_down_checkbox.hovered) *key_bind_down_checkbox.flag = !(*key_bind_down_checkbox.flag);
	if (key_bind_left_checkbox.hovered) *key_bind_left_checkbox.flag = !(*key_bind_left_checkbox.flag);
	if (key_bind_right_checkbox.hovered) *key_bind_right_checkbox.flag = !(*key_bind_right_checkbox.flag);
}
static void destroy(){

}
// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.initialize = &init;
	scene.name = "Settings";
	scene.draw = &draw;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	scene.destroy = &destroy;
	// TODO-IF: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}

// TODO-Graphical_Widget:
// Just suggestions, you can create your own usage.
	// Selecting BGM:
	// 1. Declare global variables for storing the BGM. (see `shared.h`, `shared.c`)
	// 2. Load the BGM in `shared.c`.
	// 3. Create dropdown menu for selecting BGM in setting scene, involving `scene_settings.c` and `scene_setting.h.
	// 4. Switch and play the BGM if the corresponding option is selected.

	// Adjusting Volume:
	// 1. Declare global variables for storing the volume. (see `shared.h`, `shared.c`)
	// 2. Create a slider for adjusting volume in setting scene, involving `scene_settings.c` and `scene_setting.h.
		// 2.1. You may use checkbox to switch between mute and unmute.
	// 3. Adjust the volume and play when the button is pressed.

	// Selecting Map:
	// 1. Preload the map to `shared.c`.
	// 2. Create buttons(or dropdown menu) for selecting map in setting scene, involving `scene_settings.c` and `scene_setting.h.
		// 2.1. For player experience, you may also create another scene between menu scene and game scene for selecting map.
	// 3. Create buttons(or dropdown menu) for selecting map in setting scene, involving `scene_settings.c` and `scene_setting.h.
	// 4. Switch and draw the map if the corresponding option is selected.
		// 4.1. Suggestions: You may use `al_draw_bitmap` to draw the map for previewing. 
							// But the map is too large to be drawn in original size. 
							// You might want to modify the function to allow scaling.