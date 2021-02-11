package de.my.persistence;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.TypedQuery;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;

//Repo base class, to be extended
public class ServiceRepository {

    @PersistenceContext
    protected EntityManager entityManager;

    public <E extends BaseEntity> boolean exists(final Class<E> entityClass, final String id) {
        final CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        final CriteriaQuery<Long> cq = cb.createQuery(Long.class);
        final Root<E> from = cq.from(entityClass);

        cq.select(cb.count(from));
        cq.where(cb.equal(from.get(BaseEntity_.id), id));

        final TypedQuery<Long> tq = entityManager.createQuery(cq).setMaxResults(1); // LIMIT = 1
        return tq.getSingleResult() > 0;
    }
    public <E extends BaseEntity> List<E> findAll(final Class<E> entityClass) {
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<E> cq = cb.createQuery(entityClass);
        Root<E> rootEntry = cq.from(entityClass);
        CriteriaQuery<E> all = cq.select(rootEntry);
        TypedQuery<E> allQuery = entityManager.createQuery(all);
        return allQuery.getResultList();
    }

    public <E extends BaseEntity> List<String> findAllIds(final Class<E> entityClass) {
        final CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        final CriteriaQuery<String> cq = cb.createQuery(String.class);
        final Root<E> from = cq.from(entityClass);
        cq.select(from.get(BaseEntity.ID));
        final TypedQuery<String> tq = entityManager.createQuery(cq);
        return tq.getResultList();
    }
    public <E extends BaseEntity> int deleteAll(final Class<E> entityClass) {
        final CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        final CriteriaDelete<E> cq = cb.createCriteriaDelete(entityClass);
        int affectedCount = entityManager.createQuery(cq).executeUpdate();
        return affectedCount;
    }

    public <E extends BaseEntity> E findById(final Class<E> entityClass, final String id) {
        final CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        final CriteriaQuery<E> cq = cb.createQuery(entityClass);
        final Root<E> from = cq.from(entityClass);

        cq.select(from).where(cb.equal(from.get(BaseEntity.ID), id));

        final TypedQuery<E> tq = entityManager.createQuery(cq);
        try {
            return tq.getSingleResult();
        }
        catch (NoResultException e) {
            return null;
        }
    }

    /* usage example:
        MyEntity myEntity = this.create(MyEntity.class, (MyEntity _myEntity) -> {
            _myEntity.setSomeString(str);
            _myEntity.setNumber(nr);
        });
    */
    public <E extends BaseEntity> E create(final Class<E> entityClass, Consumer<E> consumer) {
        E entity = BaseEntity.create(entityClass);
        consumer.accept(entity);
        entityManager.persist(entity);
        return entity;
    }

    public <T> Optional<T> getSingleResult(TypedQuery<T> query) {
        try {
            return Optional.ofNullable(query.getSingleResult());
        } catch (NoResultException e) {
            return Optional.empty();
        }
    }
}
