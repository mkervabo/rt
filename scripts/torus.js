#!/usr/bin/env node

const MAJOR = 0.5;
const MINOR = 0.2;
const Z = -3;

const MAX = 250;

console.log(`
name = "Torus ${MAX}"
width = 1280
height = 800

[camera]
	type = "PERSPECTIVE"
	position.x = 1.25
	position.y = -1.25
	rotation.y = 20
	rotation.x = 20
`)

for (let i = 0; i < MAX; i++) {
	const x = MAJOR * Math.cos(i / MAX * Math.PI * 2);
	const y = MAJOR * Math.sin(i / MAX * Math.PI * 2);

	console.log(`
		[[objects]]
			type = "SPHERE"
			material.type = "NORMAL"
			position = { x = ${x.toFixed(2)}, y = ${y.toFixed(2)}, z = ${Z} }
			radius = ${MINOR}
	`);
}
