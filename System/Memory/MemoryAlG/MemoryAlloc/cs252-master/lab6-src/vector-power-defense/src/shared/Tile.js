// Script for tile class

class Tile
{
    /*
    Integer xposition
    Integer yposition
    String tileColor
    Integer sideLength
    Boolean isWalkable
    Boolean isBuildable
    */

    constructor(xpos, ypos, color, walkable, buildable)
    {
        this.xposition = xpos;
        this.yposition = ypos;
        this.tileColor = color;
        this.isWalkable = walkable;
        this.isBuildable = buildable;
        this.sideLength = 1; // Constant value for size of each tile, use same units as creep size
    }
}

module.exports = Tile;
