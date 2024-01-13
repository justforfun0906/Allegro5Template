// TODO-HACKATHON 3-9: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
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
bool recording = false;
char name[100];
Button btn_record;
static void init(){
    btn_record = button_create(730, 20, 50, 50, "Assets/record.png", "Assets/record2.png");
}
static void draw(){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(
        menuFont,
        al_map_rgb(255, 255, 255),
        SCREEN_W/2,
        SCREEN_H - 150,
        ALLEGRO_ALIGN_CENTER,
        "<ENTER> Back to menu"
    );
    char output_name[100];
    sprintf(output_name, "Name: %s", name);
    al_draw_text(
        menuFont,
        al_map_rgb(255, 255, 255),
        SCREEN_W/2,
        50,
        ALLEGRO_ALIGN_CENTER,
        output_name
    );
    drawButton(btn_record);
}
static void on_key_down(int keycode) {
    if(recording){
        if(keycode<=26&&keycode>=1){//is english character
            char temp = 'A'+keycode-1;
            strcat(name, &temp);
        }else if(ALLEGRO_KEY_ENTER==keycode){
            recording = false;
            game_log("Stop Recording");
        }
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
	btn_record.hovered = buttonHover(btn_record, mouse_x, mouse_y);
}
static void on_mouse_down(){
    if(btn_record.hovered){
        recording = !recording;
        if(recording){
            game_log("Recording");
        }    
        else{
            game_log("Stop Recording");
        }
    }
}
// The only function that is shared across files.
Scene scene_leaderboard_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "leaderboard";
    scene.initialize  = &init;
	scene.draw = &draw;
	scene.on_key_down = &on_key_down;
    scene.on_mouse_move = &on_mouse_move;
    scene.on_mouse_down = &on_mouse_down;
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