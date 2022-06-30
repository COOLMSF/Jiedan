class World
{
    /*
    Tiles[][] map
    Building[] buildings
    Creep[] creeps
    */

    constructor(xsize, ysize)
    {
        this.map = [];
        for (var x = 0; x < xsize; x++) {
            for (var y = 0; y < ysize; y++) {
                this.map[x][y] = new Tile(x, y, "#444444", true, true);
            }
        }

    }
}

module.exports = World;
