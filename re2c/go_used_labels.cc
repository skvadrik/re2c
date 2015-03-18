#include "dfa.h"
#include "go.h"

namespace re2c
{

void Cases::used_labels ()
{
	for (uint i = 0; i < cases_size; ++i)
	{
		vUsedLabels.insert (cases[i].to->label);
	}
}

void Binary::used_labels ()
{
	thn->used_labels ();
	els->used_labels ();
}

void Linear::used_labels ()
{
	for (uint i = 0; i < branches.size (); ++i)
	{
		vUsedLabels.insert (branches[i].second->label);
	}
}

void If::used_labels ()
{
	switch (type)
	{
		case BINARY:
			info.binary->used_labels ();
			break;
		case LINEAR:
			info.linear->used_labels ();
			break;
	}
}

void SwitchIf::used_labels ()
{
	switch (type)
	{
		case SWITCH:
			info.cases->used_labels ();
			break;
		case IF:
			info.ifs->used_labels ();
			break;
	}
}

void Bitmap::used_labels ()
{
	if (hgo != NULL)
	{
		hgo->used_labels ();
	}
	vUsedLabels.insert (bitmap_state->label);
	if (lgo != NULL)
	{
		lgo->used_labels ();
	}
}

void CpgotoTable::used_labels ()
{
	for (uint i = 0; i < TABLE_SIZE; ++i)
	{
		vUsedLabels.insert (table[i]);
	}
}

void Cpgoto::used_labels ()
{
	if (hgo != NULL)
	{
		hgo->used_labels ();
	}
	table->used_labels ();
}

void Go::used_labels ()
{
	switch (type)
	{
		case NOT_INITIALIZED:
		case EMPTY:
		case DOT:
			break;
		case SWITCH_IF:
			info.switchif->used_labels ();
			break;
		case BITMAP:
			info.bitmap->used_labels ();
			break;
		case CPGOTO:
			info.cpgoto->used_labels ();
			break;
	}
}

} // namespace re2c
