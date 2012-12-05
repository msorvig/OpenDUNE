
void MIDI_Init(const char *device, const char *config);
void MIDI_Destroy();
bool MIDI_Available();
void MIDI_RawOutByte(unsigned char *data);
