takePlayerControl()
blendCamera("camera_2", 0.0)
wait(2.0)
spawnEnemy("pepe", "20 20 20")
wait(1.0)
launchParticles("fire", "20 0 20")
playAnimation("pepe", "burn")
wait(3.0)
blendOutCamera("camera_2", 2.0)
wait(3.0)
playAnimation("player_1", "die")
waitAnimation("player_1")
givePlayerControl()


playSound("explosion")
launchParticles("fire")
wait(2.0)
launchParticles("smoke")