#include "Quiz.hpp"
#include <raylib.h>
#include <string>

bool Quiz::Time_Finished = false;
bool Quiz::QuizAnswered = false;
bool Quiz::Collision = false;
std::string Quiz::question[10] = {" "};
std::string Quiz::choices[10][4] = {" "};
int Quiz::frameCounter = 0;
size_t Quiz::Index = 0;
Rectangle Quiz::Blocks_Pos[4] = {
    Rectangle{120, 580, 65, 65}, Rectangle{270, 580, 65, 65},
    Rectangle{420, 580, 65, 65}, Rectangle{570, 580, 65, 65}};
size_t Quiz::Score = 0;

bool Quiz::IsCollision(Vector2 obj1, Vector2 obj2) {
  Rectangle rec1 = {obj1.x, obj1.y, 48, 48};
  Rectangle rec2 = {obj2.x, obj2.y, 65, 65};
  return CheckCollisionRecs(rec1, rec2);
}

bool Quiz::IsCorrectAnswer(Vector2 obj1, size_t Index) {
  switch (Index) {
  case 0:
    return IsCollision(obj1, {120, 580});
  case 1:
    return IsCollision(obj1, {420, 580});
  case 2:
    return IsCollision(obj1, {270, 580});
  case 3:
    return IsCollision(obj1, {570, 580});
  case 4:
    return IsCollision(obj1, {570, 580});
  case 5:
    return IsCollision(obj1, {270, 580});
  case 6:
    return IsCollision(obj1, {420, 580});
  case 7:
    return IsCollision(obj1, {120, 580});
  case 8:
    return IsCollision(obj1, {120, 580});
  case 9:
    return IsCollision(obj1, {270, 580});
  default:
    return false;
  }
}

void Quiz::Draw_Blocks(Vector2 obj1) {
  int BlockIndex = 0;
  if (Collision == false) {
    for (int i = 120; i < GetScreenWidth() - BLOCK_SIZE && BlockIndex < 4;
         i += BLOCK_SIZE, BlockIndex++) {
      const Vector2 obj2 = Vector2{(float)i, 580};
      Blocks_Pos[BlockIndex] = Rectangle{obj2.x, obj2.y, 65, 65};
      if (IsCollision(obj1, obj2)) {
        Collision = true;
        QuizAnswered = true;
        if (IsCorrectAnswer(obj1, Index))
          Score++;
        break;
      }
    }
    for (int i = 120; i < GetScreenWidth() - BLOCK_SIZE; i += BLOCK_SIZE)
      DrawRectangleLines(i, 580, 65, 65, GREEN);
  }
}

bool Quiz::Check_Font_Loaded(const Font font) {
  if (font.texture.id == 0) {
    std::cout << "Font not loaded" << std::endl;
    return false;
  }
  return true;
}

void Quiz::Draw_Choices() {
  const Font font = LoadFont("../Font/Font1.ttf");
  std::string choices[4] = {"A", "B", "C", "D"};
  int blockIndex = 0;

  for (int i = 120; i < GetScreenWidth() - BLOCK_SIZE && blockIndex < 4;
       i += BLOCK_SIZE) {
    const Vector2 textPos = {static_cast<float>(i + 20), 585.0f};

    if (Collision) {
      DrawTextEx(font, TextFormat("%s", choices[blockIndex].c_str()), textPos,
                 50, 2, GREEN);
    } else if (Check_Font_Loaded(font)) {
      DrawTextEx(font, TextFormat("%s", choices[blockIndex].c_str()), textPos,
                 50, 2, GREEN);
    } else {
      DrawText("Font not loaded Use Default Font", 10, 10, 20, RED);
    }
    blockIndex++;
  }
}

void Quiz::Update_Choices() {
  const Font font = LoadFont("../Font/Font1.ttf");
  const std::string Arr[4] = {"A", "B", "C", "D"};
  if (Index < 10) {
    for (int i = 0; i < 4; ++i) {
      const Vector2 Choice_Pos = {35 + static_cast<float>(i * 200), 415};
      DrawTextEx(font,
                 TextFormat("%c:%s", Arr[i][0], choices[Index][i].c_str()),
                 Choice_Pos, 30, 2, WHITE);
    }
  }
  if (GetQuizAnswered()) {
    QuizAnswered = true;
    Index++;
  }
}

void Quiz::SetQuestion() {
  std::string Temp_Questions[10] = {
      "What is the capital of France?",
      "2! + 4! = ?",
      "What is the largest planet in our solar system?",
      "Who wrote is the author of 'Ariel'?",
      "What is the chemical symbol for water?",
      "What is the fastest land animal?",
      "What is the smallest prime number?",
      "What is the hardest natural substance on Earth?",
      "What is the main ingredient in guacamole?",
      "What is the largest mammal in the world?"};
  for (int i = 0; i < 10; i++) {
    question[i] = Temp_Questions[i];
  }
  Update_Choices();
}

void Quiz::SetChoices() {
  std::string Temp_Choices[10][4] = {
      // Question 0: Capital of France
      {"Paris", "London", "Berlin", "Madrid"},
      // Question 1: 2³ + 4² = ?
      {"24", "22", "26", "18"},
      // Question 2: Largest planet
      {"Mars", "Jupiter", "Earth", "Saturn"},
      // Question 3: Romeo and Juliet author
      {"Dickens", "Kafka", "Austen", "Plath"},
      // Question 4: Chemical symbol for water
      {"NaCl", "CO2", "O2", "H2O"},
      // Question 5: Fastest land animal
      {"Lion", "Cheetah", "Elephant", "Kangaroo"},
      // Question 6: Smallest prime number
      {"0", "3", "2", "1"},
      // Question 7: Hardest natural substance
      {"Diamond", "Ruby", "Emerald", "Graphite"},
      // Question 8: Main ingredient in guacamole
      {"Avocado", "Tomato", "Onion", "Pepper"},
      // Question 9: Largest mammal
      {"Walrus", "BlueWhale", "Camel", "Rhino"}};
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 4; ++j) {
      choices[i][j] = Temp_Choices[i][j];
    }
  }
}

void Quiz::Draw_Question() {
  const Font font = LoadFont("../Font/Font1.ttf");
  SetQuestion();
  if (Check_Font_Loaded(font)) {
    for (int i = 0; i < 10; i++) {
      std::string q = Quiz::question[i];
      const Vector2 QuestionPos = {10.0f, static_cast<float>(50 + i * 30)};
      if (IsKeyDown(KEY_SPACE)) {
        frameCounter += 2.5;
      } else
        frameCounter++;
      DrawTextEx(font,
                 TextSubtext(TextFormat("%i:%s", i + 1, q.c_str()), 0,
                             frameCounter / 35),
                 QuestionPos, 25, 2, WHITE);
    }
  } else {
    DrawText("Font not loaded Use Default Font", 10, 10, 20, RED);
  }
}

void Timer(void) {
  static float time = 60.5f;

  const Font font = LoadFont("../Font/Font1.ttf");
  const Vector2 TimePos = {static_cast<float>(GetScreenWidth() - 480), 475};
  if (font.texture.id == 0) {
    std::cout << "Font not loaded" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (!Quiz::Time_Finished) {
    time -= GetFrameTime();
    if (time <= 0.0f) {
      time = 0;
      Quiz::Time_Finished = true;
    }
    DrawTextEx(font, TextFormat("Timer:%i", (int)time), TimePos, 35, 2, YELLOW);
  }
}
