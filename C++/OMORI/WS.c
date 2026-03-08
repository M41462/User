#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

Image icon;
Font font;

typedef struct {
  Image image;
  Texture2D texture;
  Vector2 position;
  bool Is_Collision;
  Rectangle rec;
} Cat;

typedef struct {
  Image image;
  Texture2D texture;
  Vector2 position;
  bool Is_Collision;
  Rectangle rec;
} Door;

typedef struct Animation {
  int frame;
  int max_frames;
  float timer;
  float speed;
} Animation;

typedef enum {
  DIRECTION_DOWN,
  DIRECTION_UP,
  DIRECTION_LEFT,
  DIRECTION_RIGHT
} Direction;

struct OMORI {
  Vector2 Position;
  Vector2 Old_Position;
  bool Is_Frozen;
  bool Stopped;
  Image image;
  Texture2D Current_Texture;
  Texture2D Texture_Left;
  Texture2D Texture_Right;
  Texture2D Texture_Up;
  Texture2D Texture_Down;
  Direction direction;
  float speed;
  Music music;
  Sound sound;
};

void Init_Font(Font *font) {
  *font = LoadFont("./Font/OMORI_GAME.ttf");
  if (font == NULL) {
    TraceLog(LOG_ERROR, "Could not load font");
    exit(EXIT_FAILURE);
  }
}

void Init_Objects(Cat *cat, Door *door) {
  door->Is_Collision = false;
  cat->Is_Collision = false;
  cat->image = LoadImage("./Image/Cat.png");
  door->image = LoadImage("./Image/Door.jpeg");
  if (cat->image.data == NULL || door->image.data == NULL) {
    TraceLog(LOG_ERROR, "Could not load icon");
    exit(EXIT_FAILURE);
  }
  cat->texture = LoadTextureFromImage(cat->image);
  door->texture = LoadTextureFromImage(door->image);
  cat->position = (Vector2){250, 450};
  door->position = (Vector2){200, 120};

  door->rec = (Rectangle){door->position.x + 45, door->position.y + 45,
                          (door->texture.width * 0.1f) - 21,
                          (door->texture.height * 0.145f) - 40};
  cat->rec = (Rectangle){cat->position.x, cat->position.y + 15,
                         (cat->texture.width * 0.025f),
                         cat->texture.height * 0.025f - 25};

  UnloadImage(cat->image);
  UnloadImage(door->image);
}
void Init_Animation(Animation *ani) {
  ani->frame = 0;
  ani->max_frames = 4;
  ani->timer = 0.0f;
  ani->speed = 0.5f;
}

bool Check_Omori_Cat_Collision(Cat *cat, Rectangle Omori_Rec) {
  return CheckCollisionRecs(cat->rec, Omori_Rec);
}

bool Check_Omori_Door_Collision(Door *door, Rectangle Omori_Rec) {
  return CheckCollisionRecs(door->rec, Omori_Rec);
}
void Draw_Objects(Cat *cat, Door *door, Rectangle Omori_Rec) {
  static bool Show_Text = false;

  Vector2 Text_Position = {GetScreenWidth() - 400, 20};
  const Rectangle CAT = {cat->position.x - 20, cat->position.y - 10, 100, 100};
  const Rectangle DOOR = {door->position.x + 20, door->position.y + 10, 100,
                          120};

  DrawTextureEx(cat->texture, cat->position, 0.0f, 0.025f, WHITE);
  DrawTextureEx(door->texture, door->position, 0.0f, 0.2f, WHITE);

  bool coll_cat = CheckCollisionRecs(Omori_Rec, CAT);
  bool coll_door = CheckCollisionRecs(Omori_Rec, DOOR);
  bool in_collision = coll_cat || coll_door;

  if (IsKeyPressed(KEY_Z) && in_collision) {
    Show_Text = !Show_Text;
  }

  if (!in_collision) {
    Show_Text = false;
  }

  if (Show_Text) {
    if (coll_door)
      DrawTextEx(font, "You have found the door!", Text_Position, 35, 2, BLACK);
    else if (coll_cat)
      DrawTextEx(font, "Waiting for something to happen", Text_Position, 35, 2,
                 BLACK);
  }
}

void Init_Omori(struct OMORI *omori) {
  omori->speed = 2.575f;
  omori->Is_Frozen = false;
  omori->Stopped = false;
  omori->Position.x = (float)GetScreenWidth() / 2 - 20;
  omori->Position.y = (float)GetScreenHeight() / 2 - 50;
  omori->direction = DIRECTION_DOWN;
  Image imageDown = LoadImage("./Image/OMORI.png");
  Image imageUp = LoadImage("./Image/up.png");
  Image imageLeft = LoadImage("./Image/left.png");
  Image imageRight = LoadImage("./Image/right.png");
  icon = LoadImage("./Image/OMORI.png"); // TODO: for the windows icon
  if (icon.data == NULL) {
    TraceLog(LOG_ERROR, "Could not load icon");
    exit(EXIT_FAILURE);
  }

  omori->Texture_Down = LoadTextureFromImage(imageDown);
  omori->Texture_Up = LoadTextureFromImage(imageUp);
  omori->Texture_Left = LoadTextureFromImage(imageLeft);
  omori->Texture_Right = LoadTextureFromImage(imageRight);
  if (omori->Texture_Down.id == 0 || omori->Texture_Up.id == 0 ||
      omori->Texture_Left.id == 0 || omori->Texture_Right.id == 0) {
    fprintf(stderr, "Could not load textures\n");
    exit(EXIT_FAILURE);
  }

  SetTextureFilter(omori->Texture_Down, TEXTURE_FILTER_POINT);
  SetTextureFilter(omori->Texture_Up, TEXTURE_FILTER_POINT);
  SetTextureFilter(omori->Texture_Left, TEXTURE_FILTER_POINT);
  SetTextureFilter(omori->Texture_Right, TEXTURE_FILTER_POINT);

  omori->Current_Texture = omori->Texture_Down;

  UnloadImage(imageDown);
  UnloadImage(imageUp);
  UnloadImage(imageLeft);
  UnloadImage(imageRight);
}
void Move_Omori(struct OMORI *omori) {
  if (!omori->Stopped) {
    Vector2 velocity = {0};
    if (IsKeyDown(KEY_RIGHT)) {
      velocity.x += 1.0f;
      omori->Current_Texture = omori->Texture_Right;
      omori->direction = DIRECTION_RIGHT;
    }
    if (IsKeyDown(KEY_LEFT)) {
      velocity.x -= 1.0f;
      omori->Current_Texture = omori->Texture_Left;
      omori->direction = DIRECTION_LEFT;
    }
    if (IsKeyDown(KEY_UP)) {
      velocity.y -= 1.0f;
      omori->Current_Texture = omori->Texture_Up;
      omori->direction = DIRECTION_UP;
    }
    if (IsKeyDown(KEY_DOWN)) {
      velocity.y += 1.0f;
      omori->Current_Texture = omori->Texture_Down;
      omori->direction = DIRECTION_DOWN;
    }
    velocity = Vector2Scale(Vector2Normalize(velocity), omori->speed);
    omori->Position = Vector2Add(omori->Position, velocity);
  }
}
void Update_Omori_Animation(struct OMORI *omori, Animation *ani) {
  ani->timer += GetFrameTime();
  if (ani->timer >= ani->speed) {
    ani->frame = (ani->frame + 1) % ani->max_frames;
    ani->timer = 0.0f;
  }
}

bool Check_Omori_Collision(struct OMORI *omori) {
  float height = 65;
  float width = 65;
  return (omori->Position.x < 0 || omori->Position.y < 0 ||
          omori->Position.x + width > GetScreenWidth() ||
          omori->Position.y + height > GetScreenHeight());
}

void Draw_Window(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "WHITE SPACE");
  InitAudioDevice();

  SetTargetFPS(60);
  SetTextLineSpacing(16);

  Cat cat = {0};
  Door door = {0};
  struct OMORI *omori = malloc(sizeof(struct OMORI));
  Animation *ani = malloc(sizeof(Animation));
  if (omori == NULL || ani == NULL) {
    TraceLog(LOG_ERROR, "Could not allocate memory");
    exit(EXIT_FAILURE);
  }

  Init_Objects(&cat, &door);
  Init_Omori(omori);
  Init_Font(&font);
  Init_Animation(ani);

  SetWindowIcon(icon);

  omori->music = LoadMusicStream("./Sound/OMORI.mp3");
  if (omori->music.ctxData == NULL) {
    TraceLog(LOG_ERROR, "Could not load music stream");
    exit(EXIT_FAILURE);
  }

  omori->sound = LoadSound("./Sound/red-hands.mp3");
  if (omori->sound.stream.buffer == NULL) {
    TraceLog(LOG_ERROR, "Could not load sound");
    exit(EXIT_FAILURE);
  }

  SetSoundVolume(omori->sound, 0.5f);
  SetMusicVolume(omori->music, 0.5f);
  PlayMusicStream(omori->music);

  Rectangle SOURCE = {0, 0, (float)omori->Current_Texture.width,
                      (float)omori->Current_Texture.height};
  Rectangle DEST = {omori->Position.x, omori->Position.y,
                    omori->Current_Texture.width * 2.5,
                    omori->Current_Texture.height * 2.5};

  const Rectangle BOX = {250, 270, 250, 200};
  float freeze_time = 0.0f;

  while (!WindowShouldClose()) {
    omori->Old_Position = omori->Position;

    UpdateMusicStream(omori->music);
    Update_Omori_Animation(omori, ani);

    if (!omori->Is_Frozen && !omori->Stopped) {
      Move_Omori(omori);
    }
    Rectangle Omori_Rec = {omori->Position.x + 10, omori->Position.y,
                           omori->Current_Texture.width * 2.5f - 25,
                           omori->Current_Texture.height * 2.5f};
    bool collisionWithCat = Check_Omori_Cat_Collision(&cat, Omori_Rec);
    bool collisionWithDoor = Check_Omori_Door_Collision(&door, Omori_Rec);
    cat.Is_Collision = collisionWithCat;
    door.Is_Collision = collisionWithDoor;
    if (collisionWithCat || collisionWithDoor) {
      omori->Position = omori->Old_Position;
    }
    DEST.x = omori->Position.x;
    DEST.y = omori->Position.y;

    BeginDrawing();
    ClearBackground(WHITE);
    DrawRectangleLinesEx(BOX, 4, BLACK);
    Draw_Objects(&cat, &door, Omori_Rec);
    DrawTexturePro(omori->Current_Texture, SOURCE, DEST, (Vector2){0, 0}, 0.0f,
                   WHITE);

    if (Check_Omori_Collision(omori)) {
      omori->Position.x = (float)GetScreenWidth() / 2 - 20;
      omori->Position.y = (float)GetScreenHeight() / 2 - 50;
      omori->Is_Frozen = true;
      freeze_time = 1.0f;
    }
    if (omori->Is_Frozen) {
      if (freeze_time == 1.0f)
        PlaySound(omori->sound);
      freeze_time -= GetFrameTime();
      omori->Current_Texture = omori->Texture_Down;
      if (freeze_time <= 0.0f) {
        omori->Is_Frozen = false;
      }
    }

    EndDrawing();
  }
  UnloadTexture(omori->Texture_Down);
  UnloadTexture(omori->Texture_Up);
  UnloadTexture(omori->Texture_Left);
  UnloadTexture(omori->Texture_Right);
  UnloadSound(omori->sound);
  UnloadMusicStream(omori->music);
  UnloadImage(icon);
  UnloadTexture(cat.texture);
  UnloadTexture(door.texture);
  UnloadFont(font);
  CloseAudioDevice();
  CloseWindow();
  free(omori);
}

int main(int argc, char *argv[]) {
  Draw_Window();
  return EXIT_SUCCESS;
}
