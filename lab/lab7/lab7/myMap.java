
import java.util.Set;

public interface myMap<K, V> extends Iterable<K> {
    /** Removes all the mappings from this map. */
    void clear();

    /* Returns the value to which the specified key is mapped, or null if this
     * map contains no mapping for the key.
     */
    V get(K key);

    /* Returns true if this map contains a mapping for the specified key. */
    default boolean containsKey(K key) {
        return get(key) != null;
    }

    /* Associates the specified value with the specified key in this map. */
    void put(K key, V value);

    /* Returns the number of key-value mappings in this map. */
    int size();

    /* Returns a Set view of the keys contained in this map. */
    Set<K> keySet();

    /* Removes the mapping for the specified key from this map if present.
     * Not required for Lab 9. If you don't implement this, throw an
     * UnsupportedOperationException. */
    K remove(K key);

    /* Removes the entry for the specified key only if it is currently mapped to
     * the specified value. Not required for Lab 9. If you don't implement this,
     * throw an UnsupportedOperationException.*/
    K remove(K key, V value);
}
