#pragma once

namespace MNL
{
	/*
	MnModel class ONLY CONTAINS GEOMETRIC DATA. Does NOT have vertex buffer and index buffer.
	Designing own drawable class using MnModel and buffers is up to users
	*/
	class MnModel
	{
	public:
		MnModel();
		~MnModel();
	};
}