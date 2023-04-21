# Scratch-card
Casino Game
This is a simple command-line casino game written in C++. In this game, the user plays a card game against the computer. The user can bet money and win or lose based on the outcome of the game.

Prerequisites
C++ compiler
Game Rules
The user and the computer both get three cards.
The player can choose to bet money or fold.
- If the player bets, they must bet an amount less than or equal to their current balance.
- If the player bets and the computer follows, both cards are revealed and the winner is determined.
- If the player bets and the computer folds, the player wins the amount they bet.
- If the player folds, the game is over and the player loses the amount they bet.
The winner is determined based on the value of the cards according to the following hierarchy:
Wax (3 cards of the same value)
Sacred (3 cards in a row)
Three West (3 cards of different values)
Point (the sum of the values of the cards)
- If both players have the same ranking, the player with the highest card value wins.
- If the computer wins, the player loses the amount they bet.
- If the player wins, they win the amount they bet plus twice the amount they bet.
The game continues until the player runs out of money or chooses to quit.
