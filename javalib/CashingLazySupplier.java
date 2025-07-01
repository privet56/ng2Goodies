package my.utils;

import java.util.function.Supplier;

/**
 * example usage:
 * Supplier<List<MyEntity>> myEntities = new CashingLazySupplier<>(() -> myService.findAllMyEntities(myId));
 * myEntities.get();
 * myEntities.get();
 *
 * @param <T>
 */
public class CashingLazySupplier<T> implements Supplier<T> {
    private T value;
    private final Supplier<T> supplier;

    public CashingLazySupplier(Supplier<T> supplier) {
        this.supplier = supplier;
    }

    public T get() {
        if (value == null) {
            value = supplier.get(); // read (potentially large) data from db only once and only if needed
        }
        return value;
    }

    public void reset() {
        value = null;
    }
}
