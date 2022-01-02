// Script for building classes

class Building
{
    /*
    Integer xposition
    Integer yposition
    Integer towerLevel
    String buildingType
    Integer currHealth
    Integer maxHealth
    */

    constructor(xpos, ypos, type)
    {
        this.xposition = xpos;
        this.yposition = ypos;
        this.buildingType = type;
    }

    upgrade()
    {

    }

    collapse()
    {

    }
}

class OffenseTower extends Building
{
    /*
    Creep creepType
    Float bossMultiplier <-- = 1 if normal creep, > 1 if boss creep
    */

    constructor(xpos, ypos, type)
    {
        super(xpos, ypos, type);
        switch (type)
        {
            case "CreeperSpawn":
                break;
            case "QuicksterSpawn":
                break;
            case "SwarmieSpawn":
                break;
            case "RotundoSpawn":
                break;
            case "MassimoSpawn":
                break;
        }
    }

    // Spawns the creep associated with the tower type
    spawn()
    {

    }

    upgrade()
    {
        super.upgrade();
    }
}

class DefenseTower extends Building
{
    /*
    Integer baseDamage
    Float multDamage
    Integer baseRate
    Float multRate
    Integer baseRange
    Float multRange
    Integer baseSplash
    Float multSplash
    String priority
    */

    constructor(xpos, ypos, type)
    {
        super(xpos, ypos, type);

        this.baseDamage = 1;
        this.baseRate = 1;
        this.baseRange = 3.5;
        this.baseSplash = 0;

        switch (type)
        {
            // Basic tower
            case "BasicTower":
                this.baseRange = 2.5;
                break;
            // Fast shooting tower, good on Quicksters
            case "AirTower":
                this.baseRate = 2;
                break;
            // Splash damage tower, good on Swarmies
            case "WaterTower":
                this.baseSplash = 2;
                break;
            // High single shot damage tower, good on Rotundos and Massimos
            case "EarthTower":
                this.baseDamage = 2;
                break;
            // Shoots fast, splash, and high damage. Good on everything
            case "FireTower":
                this.baseRate = 2;
                this.baseSplash = 2;
                this.baseDamage = 2;
                this.baseRange = 5;
                break;
        }
    }

    // Calculate straight line distance from tower to a creep
    distanceFrom(creep)
    {
        // Pythagorean theorem.
        return Math.sqrt(Math.exp(this.xpos - creep.xpos, 2) + Math.exp(this.ypos - creep.ypos, 2));
    }

    // Deals damage to one creep based on the tower's stats
    attack(creepList)
    {
        var minDistance = -1;
        var minCreep = null;
        for (var creep in creepList) {
            var dist = this.distanceFrom(creep);
            if ((minDistance < 0) || (dist < minDistance)) {
                minCreep = creep;
            }
        }

        if ((minCreep) && (minDistance <= this.baseRange * this.multRange)) {
            minCreep.currHealth -= this.baseDamage * this.multDamage;

            if (minCreep.currHealth <= 0) {
                minCreep.perish();
            }
        }
    }

    upgrade()
    {
        super.upgrade();
    }
}

class PowerNode extends Building
{
    /*
    Integer baseIncome
    Integer currHealth
    Integer maxHealth
    */

    constructor(xpos, ypos, type, health)
    {
        super(xpos, ypos, type);
        this.currHealth = health;
        this.maxHealth = health;
        this.calculateIncome();
    }

    // Calculates the base income of the node using factors such as
    // number of players, type of node, etc.
    calculateIncome()
    {

    }

    // Generates income
    generate()
    {

    }

    upgrade()
    {
        super.upgrade;
    }
}

module.exports = Building;
