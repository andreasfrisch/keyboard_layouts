#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"
#include "action_tapping.h"

extern keymap_config_t keymap_config;

#define _BASE 0
#define _MOVE 1
#define _SYMB 2
#define _MOUSE 3
#define _FUNC 4
#define _NUMB 5
#define _SYST 6

// Fillers to make layering more clear
#define _______ KC_TRNS
#define ___X___ KC_NO

// Mac-specific shortcuts
#define MAC_SLP KC_POWER | KC_LALT | KC_LGUI
#define KC_PND LALT(KC_3)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Empty layer
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
*/


/* BASE
 * ,-----------------------------------------------------------------------------------.
 * | esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | syst | -- tap for del
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | move | Ent  | -- tap move for ;
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | func | Ctrl |  Alt |  Cmd | numb |    Space    | symb |  Cmd |  Alt | Ctrl | func |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = {
  {KC_ESC   , KC_Q   , KC_W   , KC_E   , KC_R     , KC_T  , KC_Y  , KC_U     , KC_I   , KC_O   , KC_P     , MO(_SYST)        },
  {KC_TAB   , KC_A   , KC_S   , KC_D   , KC_F     , KC_G  , KC_H  , KC_J     , KC_K   , KC_L   , MO(_MOVE), KC_ENT           },
  {KC_LSFT  , KC_Z   , KC_X   , KC_C   , KC_V     , KC_B  , KC_N  , KC_M     , KC_COMM, KC_DOT , KC_SLSH  , KC_RSFT          },
  {MO(_FUNC), KC_LCTL, KC_LALT, KC_LGUI, MO(_NUMB), KC_SPC, KC_SPC, MO(_SYMB), KC_RGUI, KC_RALT, KC_RCTL  , MO(_FUNC)        }
},

/* MOVE
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      | pgup |      |      |      |      |  Up  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | home | pgdn | end  |      |      | Left | Down | Right| >><< |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | mouse|             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOVE] = {
  {_______, ___X___, ___X___, KC_PGUP, ___X___   , ___X___, ___X___, ___X___, KC_UP  , ___X___, ___X___         , _______},
  {_______, ___X___, KC_HOME, KC_PGDN, KC_END    , ___X___, ___X___, KC_LEFT, KC_DOWN, KC_RGHT, LT(_MOVE, KC_NO), _______},
  {_______, ___X___, ___X___, ___X___, ___X___   , ___X___, ___X___, ___X___, ___X___, ___X___, ___X___         , _______},
  {_______, _______, _______, _______, TG(_MOUSE), _______, _______, _______, _______, _______, _______         , _______}
},

/* NUMBERS LAYER
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |  {   |  }   |      |      |  7   |  8   |  9   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  +   |  -   |  [   |  ]   |      |      |  4   |  5   |  6   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  *   |  /   |  (   |  )   |      |      |  1   |  2   |  3   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | >><< |  backspace  |      |  1   |  .   |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMB] = {
  {_______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, KC_7   , KC_8   , KC_9   , _______, _______},
  {_______, KC_PPLS, KC_PMNS, KC_LBRC, KC_RBRC, _______, _______, KC_4   , KC_5   , KC_6   , _______, _______},
  {_______, KC_PAST, KC_PSLS, KC_LPRN, KC_RPRN, _______, _______, KC_1   , KC_2   , KC_3   , _______, _______},
  {_______, _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, KC_0   , KC_DOT , _______, _______}
},

/* SYSTEMS LAYER
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | >><< |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | macz |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | RESET|      |      |      |      |    Sleep    |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYST] = {
  {_______, _______, _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______ , _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______ , _______, MAC_SLP, _______, _______, _______, _______, _______},
  { RESET , _______, _______, _______, _______ , KC_SLEP, KC_SLEP, _______, _______, _______, _______, _______}
},


/* SYMB
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  ;   |  {   |  }   |      |      |  &   |  \   |  =   |  `   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  +   |  -   |  [   |  ]   |      |      |  $   |  %   |  ^   |  '   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  *   |  /   |  (   |  )   |      |      |  !   |  @   |  #   |  ~   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |   delete    | >><< |      |  £   |  |   |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMB] = {
  {_______, _______, KC_SCLN, KC_LCBR, KC_RCBR, _______, _______, KC_AMPR, KC_BSLS, KC_EQL , KC_GRV , _______},
  {_______, KC_PLUS, KC_MINS, KC_LBRC, KC_RBRC, _______, _______, KC_DLR , KC_PERC, KC_CIRC, KC_QUOT, _______},
  {_______, KC_ASTR, KC_SLSH, KC_LPRN, KC_RPRN, _______, _______, KC_EXLM, KC_AT  , KC_HASH, KC_TILD, _______},
  {_______, _______, _______, _______, _______, KC_DEL , KC_DEL , _______, _______, KC_PND , KC_PIPE, _______}
},

/* MOUSE
 * ,-----------------------------------------------------------------------------------.
 * |      |      | ACC-2| ACC-1| ACC-0|      |      | SW-L |  M-U | SW-R |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | MB-3 | MB-2 | MB-1 |      |      |  M-L |  M-D |  M-R |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | SW-D | SW-U |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | mouse|      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = {
  {KC_ESC , ___X___, KC_ACL2, KC_ACL1, KC_ACL0   , ___X___, ___X___, KC_WH_L, KC_MS_U, KC_WH_R, ___X___, ___X___},
  {___X___, ___X___, KC_BTN3, KC_BTN2, KC_BTN1   , ___X___, ___X___, KC_MS_L, KC_MS_D, KC_MS_R, LT(_MOVE, KC_NO), ___X___},
  {_______, ___X___, ___X___, ___X___, ___X___   , ___X___, ___X___, KC_WH_D, KC_WH_U, ___X___, ___X___, _______},
  {_______, _______, _______, _______, TG(_MOUSE), _______, _______, _______, _______, _______, _______, _______}
},

/* FUNC
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      | vol+ |  F7  |  F8  |  F9  |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Æ   |  Ø   |  Å   |      |      | vol- |  F4  |  F5  |  F6  |  F11 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | mute |  F1  |  F2  |  F3  |  F10 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | prev | play/pause  | next |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = {
  {_______, _______, _______      , _______   , _______   , _______, _______, KC_VOLU, KC_F7  , KC_F8  , KC_F9  , _______},
  {_______, _______, LALT(KC_QUOT), LALT(KC_O), LALT(KC_A), _______, _______, KC_VOLD, KC_F4  , KC_F5  , KC_F6  , _______},
  {_______, _______, _______      , _______   , _______   , _______, _______, KC_MUTE, KC_F1  , KC_F2  , KC_F3  , _______},
  {_______, _______, _______      , _______   , KC_MPRV   , KC_MPLY, KC_MPLY, KC_MNXT, _______, _______, _______, _______}
}
};