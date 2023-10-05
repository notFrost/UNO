from settings import *
width = 1280
height = 720

#https://www.youtube.com/watch?v=AY9MnQ4x3zk


pygame.init()
pygame.display.set_caption("[nF] UNO - Python")
game = True
screen = pygame.display.set_mode((width, height))
clock = pygame.time.Clock()

test_surface = pygame.Surface((width/10, height /10))
test_surface.fill('Red')
while game:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            game = False
    screen.blit(test_surface, (width/2, height/2))


    pygame.display.update()
    clock.tick(60)
pygame.quit()