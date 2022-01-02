// Script for creep class

class Creep
{
    /*
    Integer xposition
    Integer yposition
    String creepType
    Integer creepSize
    Integer creepLevel
    Integer currHealth
    Integer maxHealth
    Integer baseSpeed
    Float multSpeed
    Integer baseDamage
    Float multDamage
    Integer baseRange
    Float multRange
    */

    // Build creep
    constructor(xpos, ypos, type, level, bossMultiplier)
    {
        this.xposition = xpos || 0;
        this.yposition = ypos || 0;
        this.creepType = type || "Creeper";
        this.creepLevel = level || 1;

        this.multSpeed += bossMultiplier;
        this.multDamage += bossMultiplier;
        this.multRange += bossMultiplier;

        this.creepSize = 1;
        this.baseSpeed = 1;
        this.baseDamage = 1;
        this.baseRange = 1;

        switch(this.creepType)
        {
            // Basic creep
            case "Creeper":
                break;
            // Creep with higher base speed, but less health
            case "Quickster":
                this.baseSpeed = 2;
                break;
            // Smaller creep that spawns in hords, but less health and damage
            case "Swarmie":
                this.baseDamage = 0.5;
                this.creepSize = 0.5;
                break;
            // Creep with highest health, but less base speed
            case "Rotundo":
                this.creepSize = 3;
                this.baseSpeed = 0.5;
                break;
            // Larger creep with higher health and damage, but lowest base speed
            case "Massimo":
                this.creepSize = 2;
                this.baseDamage = 2;
                this.baseSpeed = 0.25;
                break;
        }

        this.creepSize *= bossMultiplier;
        this.maxHealth = this.creepSize * this.creepLevel;
        this.currHealth = this.maxHealth;
    }

    // Function to deal damage to a building in range
    attack(building)
    {
        building.currHealth -= this.baseDamage * this.multDamage;

        if (building.currHealth <= 0) {
            building.collapse();
        }
    }

    // Function to begin death sequence and eventual removal
    perish()
    {

    }
}

module.exports = Creep;
