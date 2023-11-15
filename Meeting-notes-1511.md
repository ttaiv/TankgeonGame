# Meeting Notes
In this file, you are required to take notes for your weekly meetings. 
In each meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any


# Meeting 15.11.2023 15:15

**Participants**: 
1. Teemu 
2. Jaakko
3. Janne
4. Otso 

## Summary of works
1. Teemu
   
   Projectile ricochet and have a lifetime now! 

2. Jaakko 

   Made graphics and implemented to master. Battled with SFML!

3. Otso

   Refactored so much code that isn't even funny. Tank class, made basic ai for enemies. Level class first iteration

4. Janne
   Spikes and collision with obstacles implemented for tanks. 

## Challenges

1. Graphics are still a challenge, mainly seems to be issues with loading the textures.
2. Collisions in corners, seems to be an issue with SFML. 
3. Designing levels is a bit tricky under the current system

## Actions
1. Investigate sprites to improve textures
2. Implement SAT collision detection
3. Investigate a level designer or json.

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
Basically a prototype at this point. 

### TODOs
1. Otso will improve enemy AI with better movement.
2. Janne will investigate SAT collision to improve issues with tank "hitboxes" and possibly refactor collisions under "collisionmanager"
3. Teemu will improve class level to work with more levels and implement projectile collisions with other projectiles. Also possibly implement "game" class.
4. Jaakko will look into turning shapes into sprites to handle our graphics issues. Explosion to destructor?