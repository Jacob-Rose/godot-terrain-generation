extends ChunkManager

const NoiseOcatves = 4
const NoisePersistence = 2.5
const NoiseLacunarity = 2.0

var Player

# Called when the node enters the scene tree for the first time.
func _ready():
	Player = get_node("player")
	change_settings(NoiseOcatves,NoisePersistence,NoiseLacunarity)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	check_for_chunk_update(Vector2(Player.transform.origin.x,Player.transform.origin.z))
	pass
