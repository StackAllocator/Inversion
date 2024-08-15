//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include "./mock_game.h"
#include "./mock_player.h"
#include <gtest/gtest.h>

namespace Inversion {
TEST(gameTest, MockMainMenu) {
  MockMainMenu mock_menu;

  // Validate the constructor
  // invokation of the MockMainMenu class.

  ASSERT_EQ(mock_menu.m_Menu[0].m_Id, 1);
  ASSERT_EQ(mock_menu.m_Menu[1].m_Id, 2);
  ASSERT_EQ(mock_menu.m_Menu[2].m_Id, 3);

  ASSERT_EQ(mock_menu.m_Menu[0].m_Text, "FIRST");
  ASSERT_EQ(mock_menu.m_Menu[1].m_Text, "SECOND");
  ASSERT_EQ(mock_menu.m_Menu[2].m_Text, "THIRD");

  ASSERT_FLOAT_EQ(mock_menu.ball_speed, 500);
  mock_menu.ball_speed = 1;

  // -----------------------------------------
  ASSERT_EQ(mock_menu.first_ball.x, 1200);
  ASSERT_EQ(mock_menu.first_ball.y, 540);

  ASSERT_EQ(mock_menu.second_ball.x, 1600);
  ASSERT_EQ(mock_menu.second_ball.y, 540);

  ASSERT_EQ(mock_menu.third_ball.x, 1400);
  ASSERT_EQ(mock_menu.third_ball.y, 540);

  mock_menu.radius = 20;
  mock_menu.first_ball.y = 10; // 10 < 20

  ASSERT_EQ(mock_menu.first_up, false);

  mock_menu.update_balls();

  ASSERT_EQ(mock_menu.first_up, true);
  ASSERT_FLOAT_EQ(mock_menu.first_ball.y, 9);
  mock_menu.first_up = true;

  mock_menu.update_balls();

  ASSERT_FLOAT_EQ(mock_menu.first_ball.y, 10);
  //-----------------------------------------//

  mock_menu.current_mouse_pos.x = 0;
  mock_menu.current_mouse_pos.y = 0;

  // No action should be taken by default.
  ASSERT_EQ(mock_menu.m_ShouldResume, false);
  ASSERT_EQ(mock_menu.m_ShouldQuit, false);
  ASSERT_EQ(mock_menu.m_ShouldLevelSelect, false);

  mock_menu.handle_input();

  // No action should be taken with current mouse position.
  ASSERT_EQ(mock_menu.m_ShouldResume, false);
  ASSERT_EQ(mock_menu.m_ShouldQuit, false);
  ASSERT_EQ(mock_menu.m_ShouldLevelSelect, false);

  // Set mouse in first box.
  mock_menu.current_mouse_pos.x = 25;
  mock_menu.current_mouse_pos.y = 45;

  mock_menu.handle_input();

  // The mouse position is in place but the mouse is not pressed yet.
  ASSERT_EQ(mock_menu.m_ShouldResume, false);

  mock_menu.mouse_pressed = true;

  mock_menu.handle_input();

  // Now the mouse hovers over the box and is pressed.
  ASSERT_EQ(mock_menu.m_ShouldResume, true);

  // Move mouse on level selection box.
  mock_menu.current_mouse_pos.y = 75;
  mock_menu.handle_input();
  ASSERT_EQ(mock_menu.m_ShouldLevelSelect, true);

  // Move mouse on quit box.
  mock_menu.current_mouse_pos.y = 95;
  mock_menu.handle_input();
  ASSERT_EQ(mock_menu.m_ShouldQuit, true);
}

TEST(gameTest, MockGame) {
  // Instantiate mock_game object.
  MockGame mock_game;

  // Set initial game state.
  mock_game.m_GameState = MockGameState::TITLE;
  mock_game.ESCAPE_PRESSED = false;

  // Update the game based on current game state.
  mock_game.update_game();
  //---------------------------------------------------//
  ASSERT_EQ(mock_game.ESCAPE_PRESSED, false);
  ASSERT_EQ(mock_game.m_GameState, MockGameState::TITLE);
  //---------------------------------------------------//

  mock_game.ESCAPE_PRESSED = true;
  mock_game.update_game();
  // ---------------------------------------------------//
  ASSERT_EQ(mock_game.ESCAPE_PRESSED, true);
  ASSERT_EQ(mock_game.m_GameState, MockGameState::MENU);
  //----------------------------------------------------//

  mock_game.ESCAPE_PRESSED = false;
  mock_game.update_game();
  //---------------------------------------------------//
  ASSERT_EQ(mock_game.ESCAPE_PRESSED, false);
  ASSERT_EQ(mock_game.m_GameState, MockGameState::MENU);
  //---------------------------------------------------//

  mock_game.m_GameState = MockGameState::TITLE;
  mock_game.ANY_KEY_PRESSED = false;
  mock_game.ESCAPE_PRESSED = false;
  mock_game.update_game();
  //--------------------------------------------------//
  ASSERT_EQ(mock_game.ANY_KEY_PRESSED, false);
  ASSERT_EQ(mock_game.ESCAPE_PRESSED, false);
  ASSERT_EQ(mock_game.m_GameState, MockGameState::TITLE);
  //--------------------------------------------------//
  mock_game.ANY_KEY_PRESSED = true;
  mock_game.update_game();
  //---------------------------------------------------//
  ASSERT_EQ(mock_game.m_GameState, MockGameState::GAME);
  //---------------------------------------------------//
}

TEST(PlayerTest, player_test) {
  MockPlayer mock_player;
  mock_player.set_rect({100, 600}, {20, 80});
  ASSERT_EQ(mock_player.get_position().x, 100);
  ASSERT_EQ(mock_player.get_position().y, 600);

  mock_player.set_position({200, 500});
  ASSERT_EQ(mock_player.get_position().x, 200);
  ASSERT_EQ(mock_player.get_position().y, 500);

  // Set the player out of screen bounds intentionally.
  mock_player.set_position({5000, 10000});
  mock_player.move(); // Resets the player to be in screen bounds.
  ASSERT_EQ(mock_player.get_position().x, mock_player.m_Start_Pos.x);
  ASSERT_EQ(mock_player.get_position().y, mock_player.m_Start_Pos.y);

  ASSERT_EQ(mock_player.hitBottom, false);
  ASSERT_EQ(mock_player.hitTop, false);
  ASSERT_EQ(mock_player.hitSide, false);

  ASSERT_EQ(mock_player.m_Velocity.x, 0);
  ASSERT_EQ(mock_player.m_Velocity.y, 0);

  // After move this sets direction scalar to 1.
  mock_player.m_MovementState = MockActorStates::IDLE;
  mock_player.key_right_pressed = true;
  mock_player.move();
  ASSERT_EQ(mock_player.m_Velocity.x, mock_player.m_Speed);
  mock_player.key_right_pressed = false;

  mock_player.set_position({20, 1000});
  mock_player.m_MovementState = MockActorStates::RUN;
  mock_player.space_pressed = true;
  mock_player.move();
  ASSERT_EQ(mock_player.m_MovementState, MockActorStates::FALL);
  mock_player.move();
}

TEST(LevelTest, level_test) {
  MockLevelManager level_manager;
  level_manager.set_level(0);
  ASSERT_EQ(level_manager.m_Id, 0);
  level_manager.set_level(10);
  ASSERT_EQ(level_manager.m_Id, 10);
}

TEST(gameTest, MockLevelSelection) {
  MockLevelSelection mock_level_selection;
  ASSERT_EQ(mock_level_selection.mouse_pressed, false);
  mock_level_selection.current_mouse_pos.x = 0;
  mock_level_selection.current_mouse_pos.y = 0;
}
} // namespace Inversion
