#ifndef KEY_H
#define KEY_H
#include "controleur/player.h"
#include "entities.h"

/**
 * @brief The Key class
 * This class is designed to manage the different keys and check if they are take or not.
 * @see Entities
 * @author A12
 * @version 2
 */
class Key: public Entities
{
private:
    bool itsTakeKey=false; ///< Check if the key has been taken or not.
public:
    /**
     * @brief Key
     * @param aX posisition X of the key
     * @param aY posisition Y of the key
     * @param aShape invisble QRect of the key, its the hitbox of any key.
     */
    Key(int aX, int aY, std::string aPixmapLink, QRect *aShape);
    /**
     * @brief KeyTake Allows testing whether the player take the key or not/
     * @param aPlayer the player
     */
    void KeyTake(Player *aPlayer);

    /**
     * @brief getItsTakeKey
     * @return true is the key has been taken. False otherwise
     */
    bool getItsTakeKey() const;
};

#endif // KEY_H
