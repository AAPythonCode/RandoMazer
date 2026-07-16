# RandoMazer
RandoMazer is a maze with a ball in it, which you must help escape to the exit. However, despite looking like a normal maze, there's a twist:

The maze's solution changes EVERY TIME YOU PLAY IT! This means you can't memorize the solution; it changes every time!

# How it Works
Here's how the maze works, from the randomization to the way you move the ball!
## How Does the Randomization Work?
In the maze, there are a series of gates that randomly rotate to one of many specified positions. As you can see in the images below, 5 gates do this every time the player restarts the game. Since these gates either block paths or open up new ones, the maze creates a new, randomized solution EVERY TIME YOU PLAY!

> [!NOTE]
We have not tested for every impossible situation in which there is no path to the exit. However, we have found some of these situations and fixed them so they no longer occur. 

<img width="257" height="258" alt="image" src="https://github.com/user-attachments/assets/e94b3138-a8fa-41e9-bb66-fd61bf18c2d7" />

Key: 

Black line → Maze border

Blue line → Pivot point for gate

Red line → Walls that break off and rotate

<img width="4032" height="3024" alt="IMG_2117" src="https://github.com/user-attachments/assets/ee246b1a-5195-4d6b-8ce9-66f18b0ce46e" />
<img width="720" height="540" alt="img_2116_720" src="https://github.com/user-attachments/assets/1babe2fb-7e71-41d6-a6e4-f57a07bc743a" />

Each of the gates shown rotates to randomize the maze.

## How Does the Player Move the Ball?
The ball is placed inside the maze at the top: the entrance. Underneath the maze is an MG996R servo stacked on top of another MG996R servo, both of which face opposite directions to create the x and y axes (you'll see this in the images below). These servos can move and tilt the maze, moving the ball in the process. These servos are controlled by a joystick, which is programmed to move the x and y servos based on its direction. 

> [!TIP]
> The joystick provides its position with values greater than 4000! Therefore, we had to map them to values from 0-180 to control the servos directly.

<img width="720" height="540" alt="img_2119_720" src="https://github.com/user-attachments/assets/3fac0f5c-ad36-4586-8813-f5fd8206ae28" />
The joystick controls the servos which are stacked on top of each other to create the x and y maze control.

# Bill Of Materials
| Name | Price | Quantity | Link |
|------|-------|----------|------|
SG90 servos | 
MG996R servos |
3D Printed Parts |
ESP32 Dev Board |
Perf Board |
USB-C PD Adapter |
M3 Screws |
Jumper Wires |





