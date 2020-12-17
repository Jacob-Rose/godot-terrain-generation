extends ChunkManager

const LengthOfSquare = 10
var Player

# Called when the node enters the scene tree for the first time.
func _ready():
	Player = get_node("player")
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	check_for_chunk_update(Vector2(Player.transform.origin.x,Player.transform.origin.z))
	pass
