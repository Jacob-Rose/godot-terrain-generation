extends Node2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var imgSize = 256
var imgScale = 4.0
var imgSpeed = 0.5
var imgPersistance = 0.5
var imgOctaves = 3
var imgLacunarity = 2.0


var image
var texture = ImageTexture.new()
var offset = Vector2(0,0)
var noiseGen = NoiseGenerator.new()
# Called when the node enters the scene tree for the first time.
func _ready():
	image = noiseGen.getImage(imgSize, offset, imgScale, imgOctaves, imgPersistance, imgLacunarity)
	
	set_process(true)
	set_process_input(true)
	pass # Replace with function body.

func _draw():
	draw_texture(texture, Vector2(0,0))
	pass
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	offset.y += delta * imgSpeed
	
	#image = noiseGen.getImage(100, offset, imgZoom)
	image = noiseGen.getImage(imgSize, offset, imgScale, imgOctaves, imgPersistance, imgLacunarity)
	texture.create_from_image(image)
	update()
	pass
	
	
func _input(event):
	
	#if event.is_pressed():
		#if event.button_index == BUTTON_WHEEL_UP:
			#imgScale += 1.0
		#if event.button_index == BUTTON_WHEEL_DOWN:
			#imgScale -= 1.0
	if Input.is_key_pressed(KEY_W):
		imgScale -= 0.5
	if Input.is_key_pressed(KEY_E):
		imgScale += 0.5
	if Input.is_key_pressed(KEY_U):
		imgPersistance -= 0.1
	if Input.is_key_pressed(KEY_I):
		imgPersistance += 0.1
	if Input.is_key_pressed(KEY_J):
		imgLacunarity += 0.1
	if Input.is_key_pressed(KEY_K):
		imgLacunarity -= 0.1
		
	pass
