#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

static Image icon = {0};
static Font font = {0};

typedef struct {
    Image image;
    Texture2D texture;
    Vector2 position;
    bool isCollision;
    Rectangle rec;
} Cat;

typedef struct {
    Image image;
    Texture2D texture;
    Vector2 position;
    bool isCollision;
    Rectangle rec;
} Door;

typedef struct {
    int frame;
    int maxFrames;
    float timer;
    float speed;
} Animation;

typedef enum {
    DIRECTION_DOWN,
    DIRECTION_UP,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} Direction;

typedef struct {
    Vector2 position;
    Vector2 oldPosition;
    bool isFrozen;
    bool stopped;
    Image image;
    Texture2D currentTexture;
    Texture2D textureLeft;
    Texture2D textureRight;
    Texture2D textureUp;
    Texture2D textureDown;
    Direction direction;
    float speed;
    Music music;
    Sound sound;
} Omori;

static void InitFont(Font* fnt) {
    *fnt = LoadFont("./Font/OMORI_GAME.ttf");
    if (fnt->texture.id == 0) {
        TraceLog(LOG_ERROR, "Could not load font");
        exit(EXIT_FAILURE);
    }
}

static void InitObjects(Cat* cat, Door* door) {
    door->isCollision = false;
    cat->isCollision = false;
    cat->image = LoadImage("./Image/Cat.png");
    door->image = LoadImage("./Image/Door.jpeg");
    
    if (cat->image.data == NULL || door->image.data == NULL) {
        TraceLog(LOG_ERROR, "Could not load images");
        exit(EXIT_FAILURE);
    }
    
    cat->texture = LoadTextureFromImage(cat->image);
    door->texture = LoadTextureFromImage(door->image);
    cat->position = (Vector2){250, 450};
    door->position = (Vector2){200, 120};

    door->rec = (Rectangle){
        door->position.x + 45, door->position.y + 45,
        (door->texture.width * 0.1f) - 21,
        (door->texture.height * 0.145f) - 40
    };
    cat->rec = (Rectangle){
        cat->position.x, cat->position.y + 15,
        (cat->texture.width * 0.025f),
        cat->texture.height * 0.025f - 25
    };

    UnloadImage(cat->image);
    UnloadImage(door->image);
}

static void InitAnimation(Animation* ani) {
    ani->frame = 0;
    ani->maxFrames = 4;
    ani->timer = 0.0f;
    ani->speed = 0.5f;
}

static void InitOmori(Omori* omori) {
    omori->speed = 2.575f;
    omori->isFrozen = false;
    omori->stopped = false;
    omori->position.x = (float)GetScreenWidth() / 2.0f - 20.0f;
    omori->position.y = (float)GetScreenHeight() / 2.0f - 50.0f;
    omori->direction = DIRECTION_DOWN;
    
    Image imageDown = LoadImage("./Image/OMORI.png");
    Image imageUp = LoadImage("./Image/up.png");
    Image imageLeft = LoadImage("./Image/left.png");
    Image imageRight = LoadImage("./Image/right.png");
    
    icon = LoadImage("./Image/OMORI.png");
    if (icon.data == NULL) {
        TraceLog(LOG_ERROR, "Could not load window icon");
        exit(EXIT_FAILURE);
    }

    omori->textureDown = LoadTextureFromImage(imageDown);
    omori->textureUp = LoadTextureFromImage(imageUp);
    omori->textureLeft = LoadTextureFromImage(imageLeft);
    omori->textureRight = LoadTextureFromImage(imageRight);
    
    if (omori->textureDown.id == 0 || omori->textureUp.id == 0 ||
        omori->textureLeft.id == 0 || omori->textureRight.id == 0) {
        fprintf(stderr, "Could not load textures\n");
        exit(EXIT_FAILURE);
    }

    SetTextureFilter(omori->textureDown, TEXTURE_FILTER_POINT);
    SetTextureFilter(omori->textureUp, TEXTURE_FILTER_POINT);
    SetTextureFilter(omori->textureLeft, TEXTURE_FILTER_POINT);
    SetTextureFilter(omori->textureRight, TEXTURE_FILTER_POINT);

    omori->currentTexture = omori->textureDown;

    UnloadImage(imageDown);
    UnloadImage(imageUp);
    UnloadImage(imageLeft);
    UnloadImage(imageRight);
}

static void MoveOmori(Omori* omori) {
    if (omori->stopped) return;
    
    Vector2 velocity = {0};
    if (IsKeyDown(KEY_RIGHT)) {
        velocity.x += 1.0f;
        omori->currentTexture = omori->textureRight;
        omori->direction = DIRECTION_RIGHT;
    }
    if (IsKeyDown(KEY_LEFT)) {
        velocity.x -= 1.0f;
        omori->currentTexture = omori->textureLeft;
        omori->direction = DIRECTION_LEFT;
    }
    if (IsKeyDown(KEY_UP)) {
        velocity.y -= 1.0f;
        omori->currentTexture = omori->textureUp;
        omori->direction = DIRECTION_UP;
    }
    if (IsKeyDown(KEY_DOWN)) {
        velocity.y += 1.0f;
        omori->currentTexture = omori->textureDown;
        omori->direction = DIRECTION_DOWN;
    }
    velocity = Vector2Scale(Vector2Normalize(velocity), omori->speed);
    omori->position = Vector2Add(omori->position, velocity);
}

static void UpdateOmoriAnimation(Omori* omori, Animation* ani) {
    ani->timer += GetFrameTime();
    if (ani->timer >= ani->speed) {
        ani->frame = (ani->frame + 1) % ani->maxFrames;
        ani->timer = 0.0f;
    }
}

static bool CheckOmoriBoundaryCollision(Omori* omori) {
    const float height = 65.0f;
    const float width = 65.0f;
    return (omori->position.x < 0 || omori->position.y < 0 ||
            omori->position.x + width > GetScreenWidth() ||
            omori->position.y + height > GetScreenHeight());
}

static void DrawGameWindow(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "WHITE SPACE");
    InitAudioDevice();

    SetTargetFPS(60);
    SetTextLineSpacing(16);

    Cat cat = {0};
    Door door = {0};
    Omori* omori = malloc(sizeof(Omori));
    Animation* ani = malloc(sizeof(Animation));
    
    if (omori == NULL || ani == NULL) {
        TraceLog(LOG_ERROR, "Could not allocate memory");
        exit(EXIT_FAILURE);
    }

    InitObjects(&cat, &door);
    InitOmori(omori);
    InitFont(&font);
    InitAnimation(ani);

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

    Rectangle SOURCE = {0, 0, (float)omori->currentTexture.width,
                        (float)omori->currentTexture.height};
    Rectangle DEST = {omori->position.x, omori->position.y,
                     omori->currentTexture.width * 2.5f,
                     omori->currentTexture.height * 2.5f};

    const Rectangle BOX = {250, 270, 250, 200};
    float freezeTime = 0.0f;

    while (!WindowShouldClose()) {
        omori->oldPosition = omori->position;

        UpdateMusicStream(omori->music);
        UpdateOmoriAnimation(omori, ani);

        if (!omori->isFrozen && !omori->stopped) {
            MoveOmori(omori);
        }
        
        Rectangle OmoriRec = {omori->position.x + 10, omori->position.y,
                              omori->currentTexture.width * 2.5f - 25,
                              omori->currentTexture.height * 2.5f};
        
        bool collisionWithCat = CheckCollisionRecs(cat.rec, OmoriRec);
        bool collisionWithDoor = CheckCollisionRecs(door.rec, OmoriRec);
        
        cat.isCollision = collisionWithCat;
        door.isCollision = collisionWithDoor;
        
        if (collisionWithCat || collisionWithDoor) {
            omori->position = omori->oldPosition;
        }
        
        DEST.x = omori->position.x;
        DEST.y = omori->position.y;

        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangleLinesEx(BOX, 4, BLACK);
        
        DrawTextureEx(cat.texture, cat.position, 0.0f, 0.025f, WHITE);
        DrawTextureEx(door.texture, door.position, 0.0f, 0.2f, WHITE);
        
        if (CheckOmoriBoundaryCollision(omori)) {
            omori->position.x = (float)GetScreenWidth() / 2.0f - 20.0f;
            omori->position.y = (float)GetScreenHeight() / 2.0f - 50.0f;
            omori->isFrozen = true;
            freezeTime = 1.0f;
        }
        
        if (omori->isFrozen) {
            if (freezeTime == 1.0f)
                PlaySound(omori->sound);
            freezeTime -= GetFrameTime();
            omori->currentTexture = omori->textureDown;
            if (freezeTime <= 0.0f) {
                omori->isFrozen = false;
            }
        }

        DrawTexturePro(omori->currentTexture, SOURCE, DEST, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }
    
    UnloadTexture(omori->textureDown);
    UnloadTexture(omori->textureUp);
    UnloadTexture(omori->textureLeft);
    UnloadTexture(omori->textureRight);
    UnloadSound(omori->sound);
    UnloadMusicStream(omori->music);
    UnloadImage(icon);
    UnloadTexture(cat.texture);
    UnloadTexture(door.texture);
    UnloadFont(font);
    CloseAudioDevice();
    CloseWindow();
    
    free(omori);
    free(ani);
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    DrawGameWindow();
    return EXIT_SUCCESS;
}
