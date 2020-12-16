extends ChunkManager

const ChunkResource = preload("res://Floor.tscn")
const LengthOfSquare = 10
var CurrentLocationOfChunk = Vector2(0,0)
var Player
var Blocks
var FunkyDelta
var HasCame

# Called when the node enters the scene tree for the first time.
func _ready():
	FunkyDelta = 0
	HasCame = false
	Blocks = []
	Player = get_node("player")
	makeNewChunk(CurrentLocationOfChunk)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	#var needsToBeReloaded = check_for_chunk_update(Vector2(Player.transform.origin.x,Player.transform.origin.z))

	
	var children = get_children()
	
	#if needsToBeReloaded:
	#	makeNewChunk(get_central_chunk_location())
	#	pass

	pass

func makeNewChunk(newPos):
	
	
	#for node in get_children():
	#	if(node.is_instance()):
	#		pass
	#pass
	
	#Blocks.clear()
	
	var originalLocation = Vector3(newPos.x,0,newPos.y)
	
	var playerLocation = originalLocation
	var newLocation = originalLocation
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01,0,0)
	playerLocation = Vector3(18,0,0)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3 (-0.01,0,0)
	playerLocation = Vector3(-18,0,0)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0,0.01,0)
	playerLocation = Vector3(0,0,-18)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0,-0.01,0)
	playerLocation = Vector3(0,0,18)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01,-0.01,0)
	playerLocation = Vector3(18,0,18)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(-0.01,0.01,0)
	playerLocation = Vector3(-18,0,-18)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(-0.01,-0.01,0)
	playerLocation = Vector3(-18,0,18)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01,0.01,0)
	playerLocation = Vector3(18,-0,-18)
	
	create_chunk(playerLocation, newLocation)
	
	pass
