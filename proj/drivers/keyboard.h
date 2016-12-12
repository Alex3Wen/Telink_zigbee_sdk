
#pragma once

#include "../drivers/usbkeycode.h"

#define KB_RETURN_KEY_MAX	4
typedef struct{
	u8 cnt;
	u8 ctrl_key;
	u8 keycode[KB_RETURN_KEY_MAX];
	u8 padding[2];	//  for  32 bit padding,  if KB_RETURN_KEY_MAX change,  this should be changed
}kb_data_t;

typedef struct {
	kb_data_t *last_send_data;
	u32 last_send_time;
	u8 resent_no_ack_cnt;
	u8 key_pressed;
	u8 frame_no;
	u8 ack_frame_no;
}rf_kb_ctrl_t;

typedef struct{
	u8 val_org;             //  ת��ǰ
	u8 val_chg;             //  ת���
	u8 this_pressed;        //  ����scan�Ƿ���
	u8 last_pressed;        //  ����scan֮ǰ�Ѿ�����������δ����
	u32 longpress_th;       //  ��������,ms
	u32 press_start_time;   //  �ϴΰ���ʱ��
	u8 longpressed;         //  �Ѿ��ﵽ����ʱ��
	u8 processed;           //  �Ѿ������˱��γ��������������ظ�����
}kb_longpress_ctrl_t;

enum{
    KB_NOT_LONGPRESS,
	KB_IS_LONGPRESS,
    KB_KEY_RELEASE,
};

extern rf_kb_ctrl_t rf_kb_ctrl;

int kb_is_data_same(kb_data_t *a, kb_data_t *b);

static inline int kb_is_key_valid(kb_data_t *p){
	return (p->cnt || p->ctrl_key);
}
static inline void kb_set_key_invalid(kb_data_t *p){
	p->cnt = p->ctrl_key = 0;
}

int kb_check_longpress(kb_longpress_ctrl_t *ctrl, int i, int *key_idx);
void kb_init(void);

