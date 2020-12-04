extends Node2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var imgSize = 256
var imgScale = 4.0
var imgSpeed = 0.5
var imgZoom = 5.0


var image
var texture = ImageTexture.new()
var offset = Vector2(0,0)
var noiseGen = NoiseGenerator.new()
# Called when the node enters the scene tree for the first time.
func _ready():
	image = noiseGen.getImage(imgSize, offset, imgZoom)
	
	set_process_input(true)
	pass # Replace with function body.

func _draw():
	draw_texture(texture, Vector2(0,0))
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	offset.y += delta * imgSpeed
	
	image = noiseGen.getImage(100, offset, imgZoom)
	texture.create_from_image(image)
	update()
	pass
	
	
func _input(event):
	if event.is_pressed():
		if event.button_index == BUTTON_WHEEL_UP:
			imgZoom += 0.2
		if event.button_index == BUTTON_WHEEL_DOWN:
			imgZoom -= 0.2
	pass
