extends ChunkManager

const ChunkResource = preload("res://Floor.tscn")
const LengthOfSquare = 10
var CurrentLocationOfChunk = Vector2(0,0)
var Player
var Blocks

# Called when the node enters the scene tree for the first time.
func _ready():
	Blocks = []
	Player = get_node("player")
	makeNewChunk(CurrentLocationOfChunk)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	var needsToBeReloaded = check_for_chunk_update(Vector2(Player.transform.origin.x,Player.transform.origin.z))
	
	if needsToBeReloaded:
		makeNewChunk(get_central_chunk_location())
		pass

	pass

func makeNewChunk(newPos):
	
	
	#for node in get_children():
	#	if(node.is_instance()):
	#		pass
	#pass
	
	#Blocks.clear()
	
	var NewChunk = ChunkResource.instance()
	NewChunk.transform.origin = Vector3(newPos.x,0,newPos.y)
	Blocks.append(self.add_child(NewChunk))
	
	
	var NewChunk2 = ChunkResource.instance()
	NewChunk2.transform.origin = Vector3(newPos.x,0,newPos.y)
	NewChunk2.transform.origin.x += LengthOfSquare * 2
	Blocks.append(self.add_child(NewChunk2))
	
	var NewChunk3 = ChunkResource.instance()
	NewChunk3.transform.origin = Vector3(newPos.x,0,newPos.y)
	NewChunk3.transform.origin.x -= LengthOfSquare * 2
	Blocks.append(self.add_child(NewChunk3))
	
	var NewChunk4 = ChunkResource.instance()
	NewChunk4.transform.origin = Vector3(newPos.x,0,newPos.y)
	NewChunk4.transform.origin.z -= LengthOfSquare * 2
	Blocks.append(self.add_child(NewChunk4))
	
	var NewChunk5 = ChunkResource.instance()
	NewChunk5.transform.origin = Vector3(newPos.x,0,newPos.y)
	NewChunk5.transform.origin.z += LengthOfSquare * 2
	Blocks.append(self.add_child(NewChunk5))
	
	var NewChunk6 = ChunkResource.instance()
	NewChunk6.transform.origin = Vector3(newPos.x,0,newPos.y)
	NewChunk6.transform.origin.z += LengthOfSquare * 2
	NewChunk6.transform.origin.x += LengthOfSquare * 2
	Blocks.append(self.add_child(NewChunk6))
	
	var NewChunk7 = ChunkResource.instance()
	NewChunk7.transform.origin = Vector3(newPos.x,0,newPos.y)
	NewChunk7.transform.origin.z += LengthOfSquare * 2
	NewChunk7.transform.origin.x -= LengthOfSquare * 2
	Blocks.append(self.add_child(NewChunk7))
	
	var NewChunk8 = ChunkResource.instance()
	NewChunk8.transform.origin = Vector3(newPos.x,0,newPos.y)
	NewChunk8.transform.origin.z -= LengthOfSquare * 2
	NewChunk8.transform.origin.x += LengthOfSquare * 2
	Blocks.append(self.add_child(NewChunk8))
	
	var NewChunk9 = ChunkResource.instance()
	NewChunk9.transform.origin = Vector3(newPos.x,0,newPos.y)
	NewChunk9.transform.origin.z -= LengthOfSquare * 2
	NewChunk9.transform.origin.x -= LengthOfSquare * 2
	Blocks.append(self.add_child(NewChunk9))
	
	pass