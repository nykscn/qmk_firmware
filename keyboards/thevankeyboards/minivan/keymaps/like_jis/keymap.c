#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  KANJI,
  RGBRST,
  MACMODE,
  WINMODE
};

enum tapdances{
  TD_SCCL = 0,
};

// Layer Mode aliases
#define KC_TBCT  LGUI_T(KC_TAB)
#define KC_ROSF  RSFT_T(KC_RO)
#define KC_ALAP  LALT_T(KC_APP)

// Layer tap
#define KC_SPLO  LT( _LOWER, KC_SPC)
#define KC_BSRA  LT(_RAISE, KC_BSPC)
#define KC_MLAD  MO(_ADJUST)
#define KC_LN1L2 LT(_LOWER, KC_LANG2)
#define KC_LN2L1 LT(_RAISE, KC_LANG1)

#define KC_SCCL  TD(TD_SCCL)

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_arrow(
  //,-----------------------------------------------------------------------------------------------------------.
  //      Esc        Q        W        E        R        T        Y        U        I        O        P        -
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //Tab/Shift        A        S        D        F        G        H        J        K        L      ;/:    Enter
      KC_TBCT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCCL,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //    Shift        Z        X        C        V        B        N        M        ,        .        /       yen
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //     Ctrl      Alt GUI/Comm            BackSpace/Lower        Space/Raise      Alt     Menu     Ctrl
      KC_LCTL, KC_LALT, KC_LN1L2,                   KC_SPC,           KC_BSPC, KC_LN2L1, KC_RALT, KC_ALAP, KC_RCTL
  //`-----------------------------------------------------------------------------------------------------------'
  ),
  

  [_LOWER] = LAYOUT_arrow(
  //,-----------------------------------------------------------------------------------------------------------.
  //                F1       F2       F3       F4       F5        -        ^        \        [         ]  Delete
       KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //                F6       F7       F8       F9      F10        @                      
      _______,   KC_1,    KC_2,     KC_3,   KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //               F11      F12        Kana/Kanji    Enter   Delete
      _______,  KC_F11,  KC_F12, XXXXXXX,   KANJI,  KC_ENT,  KC_DEL, XXXXXXX, _______, _______,   KC_UP, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //                                                                 Adjust
      _______, _______, _______,                   _______,         _______,  KC_MLAD,   KC_LEFT, KC_DOWN, KC_RGHT
  //`-----------------------------------------------------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_arrow(
  //,-----------------------------------------------------------------------------------------------------------.
  //                 1        2        3        4        5        6        7        8        9        0        -
     XXXXXXX,  XXXXXXX,   KC_UP, XXXXXXX, KC_LPRN, KC_MINS, KC_EQL, KC_RPRN,  XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //                                                           Left     Up       Down    Right
      _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_LCBR, KC_LABK, KC_RABK, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //                                                                                ,        .        /      yen
      _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_LBRC, KC_RBRC, XXXXXXX, _______,  _______, KC_UP, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______,                   _______,         _______, XXXXXXX,    KC_LEFT, KC_DOWN, KC_RGHT
  //`-----------------------------------------------------------------------------------------------------------'
  ),
  
  [_ADJUST] = LAYOUT_arrow(
  //,-----------------------------------------------------------------------------------------------------------.
  //             Reset LEDReset  MacMode  WinMode              Home PageDown   PageUp      End
      _______,   RESET,  RGBRST, LCG_NRM, LCG_SWP, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //           LED On/Off Hue/Saturation/Value Increment    Mouse Left Down Up Right
      _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  //           LED Mode Hue/Saturation/Value Decrement      Mouse Button Left Right
      _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______,                   _______,          _______, _______, _______, _______, _______
  //`-----------------------------------------------------------------------------------------------------------'
  )
};
#define TAPPING_LAYER_TERM 220 // Custom LT Tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_BSRA:
      return TAPPING_LAYER_TERM;
    case KC_SPLO:
      return TAPPING_LAYER_TERM;
    case KC_SCCL:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    case KANJI:
      if (record->event.pressed) {
        if (keymap_config.swap_lalt_lgui == false) {
          register_code(KC_LANG2);
        } else {
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      break;
    #ifdef RGBLIGHT_ENABLE
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  return result;
}

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}