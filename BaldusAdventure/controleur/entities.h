#ifndef ENTITIES_H
#define ENTITIES_H
#include <QObject>
#include <QRect>

/**
 * @class Entities
 * @brief Base class for all game entities such as players, enemies, and obstacles.
 *
 * The Entities class provides a common interface and shared data for any object
 * within the game world that has a position, shape, and graphical representation.
 * It stores the (x, y) coordinates, a QRect hitbox, and a list of QPixmaps for rendering.
 *
 * All derived classes should inherit from this base to ensure consistent behavior.
 *
 * @see Player, Enemy, Obstacle
 * @author A12
 * @version 2
 */
class Entities : public QObject
{
    Q_OBJECT

private:
    int itsX; ///< X coordinate of the entity in the game world.
    int itsY; ///< Y coordinate of the entity in the game world.
    QRect* itsShape = nullptr; ///< Pointer to the QRect used as the hitbox.
    std::list<QPixmap>* itsPixMap = nullptr; ///< List of QPixmaps used to display the entity.

public:
    /**
     * @brief Constructs a new Entities object.
     *
     * Initializes the entity with position, shape, and optional QObject parent.
     *
     * @param aX The X position of the entity.
     * @param aY The Y position of the entity.
     * @param aShape Pointer to the QRect representing the entity's hitbox.
     * @param parent (Optional) Pointer to the QObject parent.
     */
    Entities(int aX, int aY, QRect* aShape, QObject* parent = nullptr);

    /**
     * @brief Destructor for Entities.
     *
     * Frees dynamically allocated QRect memory.
     */
    ~Entities();

    //----------- Getters and Setters -----------

    /**
     * @brief Gets the X position of the entity.
     * @return X coordinate as an integer.
     */
    int getItsX() const;

    /**
     * @brief Sets the X position of the entity.
     * @param newItsX New X coordinate.
     */
    void setItsX(int newItsX);

    /**
     * @brief Gets the Y position of the entity.
     * @return Y coordinate as an integer.
     */
    int getItsY() const;

    /**
     * @brief Sets the Y position of the entity.
     * @param newItsY New Y coordinate.
     */
    void setItsY(int newItsY);

    /**
     * @brief Gets the hitbox shape of the entity.
     * @return Pointer to the QRect hitbox.
     */
    QRect* getItsShape() const;

    /**
     * @brief Sets the hitbox shape of the entity.
     * @param newItsShape Pointer to the new QRect hitbox.
     */
    void setItsShape(QRect* newItsShape);

    /**
     * @brief Gets the list of QPixmaps used by the entity.
     * @return Pointer to a list of QPixmaps.
     */
    std::list<QPixmap>* getItsPixMap() const;

    /**
     * @brief Sets the list of QPixmaps for the entity.
     * @param newItsPixMap Pointer to the new list of QPixmaps.
     */
    void setItsPixMap(std::list<QPixmap>* newItsPixMap);
};


#endif // ENTITIES_H
