#pragma once

#include "kernel/be_entity_core_types.h"

	class BImGuiVBoxLayout: public BEntity
	{
		public:
			BImGuiVBoxLayout() {}
			virtual ~BImGuiVBoxLayout() {};
			const char* class_id() const { return "ImGuiVBoxLayout"; }
	};

	class BImGuiHBoxLayout: public BEntity
	{
		public:
			BImGuiHBoxLayout() {}
			virtual ~BImGuiHBoxLayout() {};
			const char* class_id() const { return "ImGuiHBoxLayout"; }
	};
