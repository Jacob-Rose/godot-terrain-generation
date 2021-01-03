extends ChunkManager

const NoiseOcatves = 3
const NoisePersistence = 3.0
const NoiseLacunarity = 2.0
const ImageSize = 20
const FaceSize = 2
const HeightMultiplier = 5

const LevelOneMax = 0.1
const LevelTwoMax = 0.75
const LevelThreeMax = 0.9

const LevelOneColor = Color(0,0,1,1)
const LevelTwoColor = Color(0,1,0,1)
const LevelThreeColor = Color(0.5,0.5,0.5,1)
const LevelFourColor = Color(1,1,1,1)

var Player

# Called when the node enters the scene tree for the first time.
func _ready():
	Player = get_node("player")
	change_settings(NoiseOcatves,NoisePersistence,NoiseLacunarity,ImageSize,FaceSize,HeightMultiplier)
	change_level_settings(LevelOneMax,LevelTwoMax,LevelThreeMax,LevelOneColor,LevelTwoColor,LevelThreeColor,LevelFourColor)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	check_for_chunk_update(Vector2(Player.transform.origin.x,Player.transform.origin.z))
	pass
