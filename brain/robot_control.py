import detect_markers

target_ids = {5, 4, 3, 2, 1, 0}

while target_ids:
	target = target_ids[len(target_ids)]

	detected_ids = detect_markers()
