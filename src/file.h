/* $Id$ */

#ifndef FILE_H
#define FILE_H

extern bool File_Exists(const char *filename);
extern uint8 File_Open(const char *filename, uint8 mode);
extern void File_Close(uint8 index);
extern uint32 File_Read(uint8 index, void *buffer, uint32 length);
extern uint32 File_Write(uint8 index, void *buffer, uint32 length);
extern uint32 File_Seek(uint8 index, uint32 position, uint8 mode);
extern uint32 File_GetSize(uint8 index);
extern void File_Delete(const char *filename);
extern void File_Create(const char *filename);


extern void emu_File_Exists();
extern void emu_File_Open();
extern void emu_File_Close();
extern void emu_File_Read();
extern void emu_File_Write();
extern void emu_File_Seek();
extern void emu_File_GetSize();
extern void emu_File_Delete();
extern void emu_File_Create();
extern void emu_File_Obsolete1();
extern void emu_File_Obsolete2();
extern void emu_File_Obsolete3();
extern void emu_File_Obsolete4();

#endif /* FILE_H */