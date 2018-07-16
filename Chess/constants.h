#ifndef CONSTANTS_H
#define CONSTANTS_H

enum Color { white = 1, black = -1};

const int UP    = 1 ;
const int DOWN  = -1;
const int RIGHT = 1 ;
const int LEFT  = -1;
const int NONE  = 0 ;

const int PAWN_ADVANCE_X[] = { NONE };
const int PAWN_ADVANCE_Y[] = { UP   };

const int PAWN_JUMP_X[] = { NONE };
const int PAWN_JUMP_Y[] = { 2*UP };

const int PAWN_CAPTURE_X[] = { LEFT , RIGHT };
const int PAWN_CAPTURE_Y[] = { UP   , UP    };

const int PAWN_ADJACENT_X[] = { LEFT , RIGHT };
const int PAWN_ADJACENT_Y[] = { NONE , NONE  };

const int ROOK_X[] = { RIGHT, LEFT, NONE, NONE };
const int ROOK_Y[] = { NONE , NONE, UP  , DOWN };

const int KNIGHT_X[] = { 2*LEFT , 2*LEFT , LEFT   , LEFT , RIGHT  , RIGHT , 2*RIGHT , 2*RIGHT };
const int KNIGHT_Y[] = { DOWN   , UP     , 2*DOWN , 2*UP , 2*DOWN , 2*UP  , DOWN    , UP      };

const int BISHOP_X[] = { RIGHT, LEFT, RIGHT, LEFT };
const int BISHOP_Y[] = { UP   , UP  , DOWN , DOWN };

const int QUEEN_X[] = { RIGHT, LEFT, NONE, NONE, RIGHT, LEFT, RIGHT, LEFT };
const int QUEEN_Y[] = { NONE , NONE, UP  , DOWN, UP   , UP  , DOWN , DOWN };

const int KING_X[] = { RIGHT, LEFT, NONE, NONE, RIGHT, LEFT, RIGHT, LEFT };
const int KING_Y[] = { NONE , NONE, UP  , DOWN, UP   , UP  , DOWN , DOWN };

const int KING_CASTLE_X[] = { 2*LEFT , 2*RIGHT };
const int KING_CASTLE_Y[] = { NONE   , NONE    };

const int ROOK_CASTLE_X[] = { 3*RIGHT, 2*LEFT  };
const int ROOK_CASTLE_Y[] = { NONE   , NONE    };

const int SIDE_ROOK_X[]   = { 4*LEFT, 3*RIGHT };
const int SIDE_ROOK_Y[]   = { NONE   ,NONE    };

#endif // CONSTANTS_H
