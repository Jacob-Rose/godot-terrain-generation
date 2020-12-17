extends ChunkManager

const LengthOfSquare = 10
var Player

# Called when the node enters the scene tree for the first time.
func _ready():
	Player = get_node("player")
	makeNewChunk(Vector2(0,0))
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var needsToBeReloaded = check_for_chunk_update(Vector2(Player.transform.origin.x,Player.transform.origin.z))
	
	if needsToBeReloaded:
		makeNewChunk(get_central_chunk_location())
		pass

	pass

func makeNewChunk(newPos):
	
	for node in get_children():
		if(node is Chunk):
			remove_child(node)
			pass
	pass
	
	var multiplierX = (newPos.x / (LengthOfSquare * 2))
	var multiplierY = (newPos.y / (LengthOfSquare * 2))
	
	var playerLocation = Vector3(((LengthOfSquare * 2) - 2) * multiplierX,0,((LengthOfSquare * 2) - 2) * multiplierY)
	var newLocation = Vector3(0.01 * multiplierX, 0.01 * -(multiplierY),0)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01 * (multiplierX + 1),0.01 * -(multiplierY),0)
	playerLocation = Vector3(((LengthOfSquare * 2) - 2) * (multiplierX + 1),0,((LengthOfSquare * 2) - 2) * multiplierY)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3 (0.01 * (multiplierX - 1),0.01 * -(multiplierY),0)
	playerLocation = Vector3(((LengthOfSquare * 2) - 2) * (multiplierX - 1),0,((LengthOfSquare * 2) - 2) * multiplierY)
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01 * multiplierX,0.01 * -(multiplierY + 1),0)
	playerLocation = Vector3(((LengthOfSquare * 2) - 2) * multiplierX,0,((LengthOfSquare * 2) - 2) * (multiplierY + 1))
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01 * multiplierX,0.01 * -(multiplierY - 1),0)
	playerLocation = Vector3(((LengthOfSquare * 2) - 2) * multiplierX,0,((LengthOfSquare * 2) - 2) * (multiplierY - 1))
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01 * (multiplierX + 1),0.01 * -(multiplierY + 1),0)
	playerLocation = Vector3(((LengthOfSquare * 2) - 2) * (multiplierX + 1),0,((LengthOfSquare * 2) - 2) * (multiplierY + 1))
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01 * (multiplierX - 1),0.01 * -(multiplierY - 1),0)
	playerLocation = Vector3(((LengthOfSquare * 2) - 2) * (multiplierX - 1),0,((LengthOfSquare * 2) - 2) * (multiplierY - 1))
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01 * (multiplierX + 1),0.01 * -(multiplierY - 1),0)
	playerLocation = Vector3(((LengthOfSquare * 2) - 2) * (multiplierX + 1),0,((LengthOfSquare * 2) - 2) * (multiplierY - 1))
	
	create_chunk(playerLocation, newLocation)
	
	newLocation = Vector3(0.01 * (multiplierX - 1),0.01 * -(multiplierY + 1),0)
	playerLocation = Vector3(((LengthOfSquare * 2) - 2) * (multiplierX - 1),0,((LengthOfSquare * 2) - 2) * (multiplierY + 1))
	
	create_chunk(playerLocation, newLocation)
	
	pass
