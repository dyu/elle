#ifndef HOLE_KEY_HH
# define HOLE_KEY_HH

# include <QtGlobal>
# include "hole/FreeList.hh"
# include "hole/Cmp.hh"

class QDataStream;

namespace hole
{
  struct Key : public FreeList<Key>, public Cmp<Key, Key>
  {
    Key();

    quint8 data[20];

    /** Compares two keys
     * \li returns 1 if other is lesser than this
     * \li returns 0 if other is equals to this
     * \li returns -1 if other is greater than this */
    int Cmp(const Key & other) const;
  };

  QDataStream & operator<<(QDataStream & ds, const Key & key);
  QDataStream & operator>>(QDataStream & ds, Key & key);
}

#endif /* !HOLE_KEY_HH */
