#include "HID.h"

#define d_gpio_up 2
#define d_gpio_down 3
#define d_gpio_left 4
#define d_gpio_right 5
#define d_gpio_fire 6

#define d_code_up 0x60
#define d_code_down 0x5A
#define d_code_left 0x5C
#define d_code_right 0x5E
#define d_code_fire 0x62


typedef struct
{
  uint8_t modifiers_ui8;
  uint8_t reserved_ui8;
  uint8_t keys_sui8[6];
} key_report;

static const uint8_t hid_report_descriptor_sui8[] PROGMEM =
{
  //  Keyboard
  0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
  0x09, 0x06,                    // USAGE (Keyboard)
  0xa1, 0x01,                    // COLLECTION (Application)
  0x85, 0x02,                    // REPORT_ID (2)
  0x05, 0x07,                    // USAGE_PAGE (Keyboard)
  
  0x19, 0xe0,                    // USAGE_MINIMUM (Keyboard LeftControl)
  0x29, 0xe7,                    // USAGE_MAXIMUM (Keyboard Right GUI)
  0x15, 0x00,                    // LOGICAL_MINIMUM (0)
  0x25, 0x01,                    // LOGICAL_MAXIMUM (1)
  0x75, 0x01,                    // REPORT_SIZE (1)
  
  0x95, 0x08,                    // REPORT_COUNT (8)
  0x81, 0x02,                    // INPUT (Data,Var,Abs)
  0x95, 0x01,                    // REPORT_COUNT (1)
  0x75, 0x08,                    // REPORT_SIZE (8)
  0x81, 0x03,                    // INPUT (Cnst,Var,Abs)
  
  0x95, 0x06,                    // REPORT_COUNT (6)
  0x75, 0x08,                    // REPORT_SIZE (8)
  0x15, 0x00,                    // LOGICAL_MINIMUM (0)
  0x25, 0x73,                    // LOGICAL_MAXIMUM (115)
  0x05, 0x07,                    // USAGE_PAGE (Keyboard)
  
  0x19, 0x00,                    // USAGE_MINIMUM (Reserved (no event indicated))
  0x29, 0x73,                    // USAGE_MAXIMUM (Keyboard Application)
  0x81, 0x00,                    // INPUT (Data,Ary,Abs)
  0xc0,                          // END_COLLECTION
};

// Keyboard
key_report data_key_report;
volatile uint8_t send_ui8 = 0;
// Button
volatile static uint8_t up_key_ui8 = 1;
volatile static uint8_t down_key_ui8 = 1;
volatile static uint8_t left_key_ui8 = 1;
volatile static uint8_t right_key_ui8 = 1;
volatile static uint8_t fire_key_ui8 = 1;
volatile static uint8_t up_key_old_ui8 = 1;
volatile static uint8_t down_key_old_ui8 = 1;
volatile static uint8_t left_key_old_ui8 = 1;
volatile static uint8_t right_key_old_ui8 = 1;
volatile static uint8_t fire_key_old_ui8 = 1;

void set_hid_report(uint8_t key_ui8);

void setup()
{
  // Set serial port debug
  //Serial.begin( 115200 );
  // Initial wait
  delay(100);
  // Initialization USB HID keyboard stack
  static HIDSubDescriptor node_hidsubdescriptor(hid_report_descriptor_sui8, sizeof(hid_report_descriptor_sui8));
  HID().AppendDescriptor(&node_hidsubdescriptor);
  data_key_report.modifiers_ui8 = 0x00;
  data_key_report.keys_sui8[0] = 0x00;
  data_key_report.keys_sui8[1] = 0x00;
  data_key_report.keys_sui8[2] = 0x00;
  data_key_report.keys_sui8[3] = 0x00;
  data_key_report.keys_sui8[4] = 0x00;
  data_key_report.keys_sui8[5] = 0x00;
  // initialze button
  pinMode(d_gpio_up, INPUT_PULLUP);
  pinMode(d_gpio_down, INPUT_PULLUP);
  pinMode(d_gpio_left, INPUT_PULLUP);
  pinMode(d_gpio_right , INPUT_PULLUP);
  pinMode(d_gpio_fire, INPUT_PULLUP);
}

void loop()
{
  // Read UP jojstick button
  up_key_ui8 = digitalRead(d_gpio_up);
  if (up_key_old_ui8 != up_key_ui8)
  {
     if (!up_key_ui8)
    {
      set_hid_report(d_code_up);
    }
    else
    {
      set_hid_report((d_code_up + 0x80));
    }
    up_key_old_ui8 = up_key_ui8;
  }
  // Read DOWN jojstick button
  down_key_ui8 = digitalRead(d_gpio_down);
  if (down_key_old_ui8 != down_key_ui8)
  {
    if (!down_key_ui8)
    {
      set_hid_report(d_code_down);
    }
    else
    {
      set_hid_report((d_code_down + 0x80));
    }
    down_key_old_ui8 = down_key_ui8;
  }
  // Read LEFT jojstick button
  left_key_ui8 = digitalRead(d_gpio_left);
  if (left_key_old_ui8 != left_key_ui8)
  {
    if (!left_key_ui8)
    {
      set_hid_report(d_code_left);
    }
    else
    {
      set_hid_report((d_code_left + 0x80));
    }
    left_key_old_ui8 = left_key_ui8;
  }
  // Read RIGHT jojstick button
  right_key_ui8 = digitalRead(d_gpio_right);
  if (right_key_old_ui8 != right_key_ui8)
  {
    if (!right_key_ui8)
    {
      set_hid_report(d_code_right);
    }
    else
    {
      set_hid_report((d_code_right + 0x80));
    }
    right_key_old_ui8 = right_key_ui8;
  }
  // Read FIRE jojstick button
  fire_key_ui8 = digitalRead(d_gpio_fire);
  if (fire_key_old_ui8 != fire_key_ui8)
  {
    if (!fire_key_ui8)
    {
      set_hid_report(d_code_fire);
    }
    else
    {
      set_hid_report((d_code_fire + 0x80));
    }
    fire_key_old_ui8 = fire_key_ui8;
  }
  // Send HID report
  if (send_ui8)
  {
    // Debug report data
    /*Serial.print(data_key_report.modifiers_ui8, HEX);
    Serial.print("-");
    Serial.print(data_key_report.keys_sui8[0], HEX);
    Serial.print(",");
    Serial.print(data_key_report.keys_sui8[1], HEX);
    Serial.print(",");
    Serial.print(data_key_report.keys_sui8[2], HEX);
    Serial.print(",");
    Serial.print(data_key_report.keys_sui8[3], HEX);
    Serial.print(",");
    Serial.print(data_key_report.keys_sui8[4], HEX);
    Serial.print(",");
    Serial.println(data_key_report.keys_sui8[5], HEX);*/
    // Send report
    HID().SendReport(2,&data_key_report,sizeof(key_report));
    send_ui8 = 0;
  }
  delay(5);
}

void set_hid_report(uint8_t key_ui8)
{
uint8_t key_cnt_ui8;
 
  // Send scan code
  if (key_ui8 & 0x80)
  {
    for (key_cnt_ui8 = 0; key_cnt_ui8 < 6; key_cnt_ui8++)
    {
      if (0 != key_ui8 && data_key_report.keys_sui8[key_cnt_ui8] == (key_ui8 & 0x7F))
      {
        data_key_report.keys_sui8[key_cnt_ui8] = 0x00;
      }
    }
  }
  else
  {
    if (
        data_key_report.keys_sui8[0] != key_ui8 && data_key_report.keys_sui8[1] != key_ui8 && 
        data_key_report.keys_sui8[2] != key_ui8 && data_key_report.keys_sui8[3] != key_ui8 &&
        data_key_report.keys_sui8[4] != key_ui8 && data_key_report.keys_sui8[5] != key_ui8
       )
    {
      for (key_cnt_ui8 = 0; key_cnt_ui8 < 6; key_cnt_ui8++)
      {
        if (data_key_report.keys_sui8[key_cnt_ui8] == 0x00)
        {
          data_key_report.keys_sui8[key_cnt_ui8] = key_ui8;
          break;
        }
      }
    }
  }
  send_ui8 = 1;
  return;
}
