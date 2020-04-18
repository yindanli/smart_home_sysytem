void speak_open_door(){//欢迎回家，门已打开
  unsigned char i = 0;
  unsigned char head[35];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x20;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xBB;
  head[19] = 0xB6;
  head[20] = 0xD3;
  head[21] = 0xAD;
  head[22] = 0xBB;
  head[23] = 0xD8;
  head[24] = 0xBC;
  head[25] = 0xD2;
  head[26] = 0xC3;
  head[27] = 0xC5;
  head[28] = 0xD2;
  head[29] = 0xD1;
  head[30] = 0xB4;
  head[31] = 0xF2;
  head[32] = 0xBF;
  head[33] = 0xAA;
  head[34] = 0x98;

  for(i=0; i<35; i++){
    Serial.write(head[i]);
  }
}

void speak_close_door(){//门已关闭
  unsigned char i = 0;
  unsigned char head[27];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x18;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xC3;
  head[19] = 0xC5;
  head[20] = 0xD2;
  head[21] = 0xD1;
  head[22] = 0xB9;
  head[23] = 0xD8;
  head[24] = 0xB1;
  head[25] = 0xD5;
  head[26] = 0x88;

  for(i=0; i<27; i++){
    Serial.write(head[i]);
  }
}

void speak_smoke(){ //检测到烟雾
  unsigned char i = 0;
  unsigned char head[28];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x19;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x35;
  head[12] = 0x5D;
  head[13] = 0x5B;
  head[14] = 0x74;
  head[15] = 0x35;
  head[16] = 0x5D;
  head[17] = 0xBC;
  head[18] = 0xEC;
  head[19] = 0xB2;
  head[20] = 0xE2;
  head[21] = 0xB5;
  head[22] = 0xBD;
  head[23] = 0xD1;
  head[24] = 0xCC;
  head[25] = 0xCE;
  head[26] = 0xED;
  head[27] = 0x8B;

  for(i=0; i<28; i++){
    Serial.write(head[i]);
  }
}

void speak_smoke_close(){//警报已解除
  unsigned char i = 0;
  unsigned char head[29];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x1A;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xBE;
  head[19] = 0xAF;
  head[20] = 0xB1;
  head[21] = 0xA8;
  head[22] = 0xD2;
  head[23] = 0xD1;
  head[24] = 0xBD;
  head[25] = 0xE2;
  head[26] = 0xB3;
  head[27] = 0xFD;
  head[28] = 0x90;

  for(i=0; i<29; i++){
    Serial.write(head[i]);
  }
}

void speak_open_sittingroom(){//客厅灯已打开
  unsigned char i = 0;
  unsigned char head[31];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x1C;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xBF;
  head[19] = 0xCD;
  head[20] = 0xCC;
  head[21] = 0xFC;
  head[22] = 0xB5;
  head[23] = 0xC6;
  head[24] = 0xD2;
  head[25] = 0xD1;
  head[26] = 0xB4;
  head[27] = 0xF2;
  head[28] = 0xBF;
  head[29] = 0xAA;
  head[30] = 0xED;

  for(i=0; i<31; i++){
    Serial.write(head[i]);
  }

}

void speak_close_sittingroom(){//客厅灯已关闭
  unsigned char i = 0;
  unsigned char head[31];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x1C;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xBF;
  head[19] = 0xCD;
  head[20] = 0xCC;
  head[21] = 0xFC;
  head[22] = 0xB5;
  head[23] = 0xC6;
  head[24] = 0xD2;
  head[25] = 0xD1;
  head[26] = 0xB9;
  head[27] = 0xD8;
  head[28] = 0xB1;
  head[29] = 0xD5;
  head[30] = 0xBB;

  for(i=0; i<31; i++){
    Serial.write(head[i]);
  }
}

void speak_open_bedroom(){//卧室灯已打开
  unsigned char i = 0;
  unsigned char head[31];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x1C;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xCE;
  head[19] = 0xD4;
  head[20] = 0xCA;
  head[21] = 0xD2;
  head[22] = 0xB5;
  head[23] = 0xC6;
  head[24] = 0xD2;
  head[25] = 0xD1;
  head[26] = 0xB4;
  head[27] = 0xF2;
  head[28] = 0xBF;
  head[29] = 0xAA;
  head[30] = 0xAD;

  for(i=0; i<31; i++){
    Serial.write(head[i]);
  }
}

void speak_close_bedroom(){//卧室灯已关闭
  unsigned char i = 0;
  unsigned char head[31];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x1C;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xCE;
  head[19] = 0xD4;
  head[20] = 0xCA;
  head[21] = 0xD2;
  head[22] = 0xB5;
  head[23] = 0xC6;
  head[24] = 0xD2;
  head[25] = 0xD1;
  head[26] = 0xB9;
  head[27] = 0xD8;
  head[28] = 0xB1;
  head[29] = 0xD5;
  head[30] = 0xFB;

  for(i=0; i<31; i++){
    Serial.write(head[i]);
  }
}

void speak_open_hotwater(){//热水器已打开
  unsigned char i = 0;
  unsigned char head[31];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x1C;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xC8;
  head[19] = 0xC8;
  head[20] = 0xCB;
  head[21] = 0xAE;
  head[22] = 0xC6;
  head[23] = 0xF7;
  head[24] = 0xD2;
  head[25] = 0xD1;
  head[26] = 0xB4;
  head[27] = 0xF2;
  head[28] = 0xBF;
  head[29] = 0xAA;
  head[30] = 0x88;

  for(i=0; i<31; i++){
    Serial.write(head[i]);
  }
}

void speak_close_hotwater(){//热水器已关闭
  unsigned char i = 0;
  unsigned char head[31];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x1C;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xC8;
  head[19] = 0xC8;
  head[20] = 0xCB;
  head[21] = 0xAE;
  head[22] = 0xC6;
  head[23] = 0xF7;
  head[24] = 0xD2;
  head[25] = 0xD1;
  head[26] = 0xB9;
  head[27] = 0xD8;
  head[28] = 0xB1;
  head[29] = 0xD5;
  head[30] = 0xDE;

  for(i=0; i<31; i++){
    Serial.write(head[i]);
  }
}

void speak_open_fan(){//净化器已打开
  unsigned char i = 0;
  unsigned char head[31];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x1C;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xBE;
  head[19] = 0xBB;
  head[20] = 0xBB;
  head[21] = 0xAF;
  head[22] = 0xC6;
  head[23] = 0xF7;
  head[24] = 0xD2;
  head[25] = 0xD1;
  head[26] = 0xB4;
  head[27] = 0xF2;
  head[28] = 0xBF;
  head[29] = 0xAA;
  head[30] = 0xFC;

  for(i=0; i<31; i++){
    Serial.write(head[i]);
  }
}

void speak_close_fan(){//净化器已关闭
  unsigned char i = 0;
  unsigned char head[31];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x1C;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x31;
  head[12] = 0x30;
  head[13] = 0x5D;
  head[14] = 0x5B;
  head[15] = 0x74;
  head[16] = 0x35;
  head[17] = 0x5D;
  head[18] = 0xBE;
  head[19] = 0xBB;
  head[20] = 0xBB;
  head[21] = 0xAF;
  head[22] = 0xC6;
  head[23] = 0xF7;
  head[24] = 0xD2;
  head[25] = 0xD1;
  head[26] = 0xB9;
  head[27] = 0xD8;
  head[28] = 0xB1;
  head[29] = 0xD5;
  head[30] = 0xAA;

  for(i=0; i<31; i++){
    Serial.write(head[i]);
  }
}

//窗户
void speak_open_window(){//窗户已打开
  unsigned char i = 0;
  unsigned char head[28];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x19;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x35;
  head[12] = 0x5D;
  head[13] = 0x5B;
  head[14] = 0x74;
  head[15] = 0x35;
  head[16] = 0x5D;
  head[17] = 0xB4;
  head[18] = 0xB0;
  head[19] = 0xBB;
  head[20] = 0xA7;
  head[21] = 0xD2;
  head[22] = 0xD1;
  head[23] = 0xB4;
  head[24] = 0xF2;
  head[25] = 0xBF;
  head[26] = 0xAA;
  head[27] = 0xF5;

  for(i=0; i<28; i++){
    Serial.write(head[i]);
  }
}

void speak_close_window(){//窗户已关闭
  unsigned char i = 0;
  unsigned char head[28];

  head[0] = 0xFD;
  head[1] = 0x00;
  head[2] = 0x19;
  head[3] = 0x01;
  head[4] = 0x00;
  head[5] = 0x5B;
  head[6] = 0x6D;
  head[7] = 0x31;
  head[8] = 0x5D;
  head[9] = 0x5B;
  head[10] = 0x76;
  head[11] = 0x35;
  head[12] = 0x5D;
  head[13] = 0x5B;
  head[14] = 0x74;
  head[15] = 0x35;
  head[16] = 0x5D;
  head[17] = 0xB4;
  head[18] = 0xB0;
  head[19] = 0xBB;
  head[20] = 0xA7;
  head[21] = 0xD2;
  head[22] = 0xD1;
  head[23] = 0xB9;
  head[24] = 0xD8;
  head[25] = 0xB1;
  head[26] = 0xD5;
  head[27] = 0xA3;

  for(i=0; i<28; i++){
    Serial.write(head[i]);
  }
}
