#ifndef WALL_H
#define WALL_H

/** 
    * @file Wall.h
    * @brief Class representing walls in the Bomberman game.
    * @details Contains base Wall class and derived BreakableWall and UnbreakableWall classes.
*/

/** 
    * @class Wall
    * @brief Base class for walls on the map.
*/

class Wall {
protected:
    bool destructible; ///< True if wall can be destroyed by bombs
public:
    /**
     * @brief Constructor for Wall
     * @param d True if wall is destructible
     * @post Creates a wall with destructible property
     */
    Wall(bool d) : destructible(d) {}
    virtual ~Wall() {}  ///< Virtual destructor for proper cleanup
    
    /**
     * @brief Checks if the wall can be destroyed
     * @return True if destructible, false otherwise
     */
    bool isDestructible() const { return destructible; }
};

/**
 * @class BreakableWall
 * @brief Represents a wall that can be destroyed by bombs.
 */
class BreakableWall : public Wall {
public:
    BreakableWall() : Wall(true) {}
};

/**
 * @class UnbreakableWall
 * @brief Represents a wall that cannot be destroyed by bombs.
 */

class UnbreakableWall : public Wall {
public:
    UnbreakableWall() : Wall(false) {}
};

#endif