#include <TinyPngOut.h>
#include <cs50.h>
#include <qrcodegen/qrcodegen.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define SCALE 10

typedef enum Mask {
  qrcodegen_MASK_0 = 0,
  qrcodegen_MASK_1,
  qrcodegen_MASK_2,
  qrcodegen_MASK_3,
  qrcodegen_MASK_4,
  qrcodegen_MASK_5,
  qrcodegen_MASK_6,
  qrcodegen_MASK_7,
} Mask;

int Get_Mask_Number() {
  int MaskNumber;
  do {
    MaskNumber = get_int("Enter your MaskNumber (0 - 7) : ");
  } while (MaskNumber < 0 || MaskNumber > 7);
  return MaskNumber;
}

Mask Convert_Int_Mask(int MaskNumber) { return (Mask)MaskNumber; }

void Create_QrCode(struct TinyPngOut writer, uint8_t *qr0, int size) {

  uint8_t black_color[3] = {0, 0, 0};
  uint8_t white_color[3] = {255, 255, 255};
  for (int y = 0; y < size * SCALE; y++) {
    for (int x = 0; x < size * SCALE; x++) {
      bool color = qrcodegen_getModule(qr0, x / SCALE, y / SCALE);
      switch ((int)color) {
      case 1:
        TinyPngOut_write(&writer, black_color, 1);
        break;
      case 0:
        TinyPngOut_write(&writer, white_color, 1);
        break;
      }
    }
  }
}

FILE *Init_File(string filepath) {
  FILE *filepointer = fopen(filepath, "wb");
  if (filepointer == NULL) {
    perror("Error Creating file");
    return NULL;
  }
  return filepointer;
}

bool Check_TinyPNG_Init(struct TinyPngOut *writer, int width, int height,
                        FILE *filepointer) {
  if (TinyPngOut_init(writer, width, height, filepointer) != TINYPNGOUT_OK) {
    perror("Error Init TinyPngOut");
    return false;
  }
  return true;
}

int main(int argc, char const *argv[]) {
  (void)argc;
  (void)argv;
  const string filepath = "./output.png";
  FILE *filepointer = Init_File(filepath);

  int masknumber = Get_Mask_Number();
  Mask masks = Convert_Int_Mask(masknumber);
  enum qrcodegen_Mask maskversion = (enum qrcodegen_Mask)masks;

  uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
  uint8_t qr0[qrcodegen_BUFFER_LEN_MAX];

  string qrCodeText = get_string("Enter your scripted qrcode text : ");

  bool ok = qrcodegen_encodeText(qrCodeText, tempBuffer, qr0,
                                 qrcodegen_Ecc_MEDIUM, qrcodegen_VERSION_MIN,
                                 qrcodegen_VERSION_MAX, maskversion, true);
  if (!ok) {
    perror("Error function qrcodegen_encodeText");
    return EXIT_FAILURE;
  }

  int size = qrcodegen_getSize(qr0);
  printf("size of the qrcode : %d\n", size);
  struct TinyPngOut writer;

  if (!Check_TinyPNG_Init(&writer, size * SCALE, size * SCALE, filepointer)) {
    perror("Error Init TinyPng\n");
    return 1;
  }

  Create_QrCode(writer, qr0, size); // Add the Qrcode logic

  fclose(filepointer);

  return EXIT_SUCCESS;
}
