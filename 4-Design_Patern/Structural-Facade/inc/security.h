#ifndef SECURITY_H
#define SECURITY_H

typedef struct Security Security;

typedef struct {
    void (*arm_perimeter)(Security* self);
    void (*disarm)(Security* self);
    void (*enable_cameras)(Security* self, int on); // 0/1
} SecurityOps;

struct Security {
    const SecurityOps* ops;
    void* impl;
};

static inline void security_arm_perimeter(Security* s) { if (s && s->ops && s->ops->arm_perimeter) s->ops->arm_perimeter(s); }
static inline void security_disarm(Security* s) { if (s && s->ops && s->ops->disarm) s->ops->disarm(s); }
static inline void security_enable_cameras(Security* s, int on) { if (s && s->ops && s->ops->enable_cameras) s->ops->enable_cameras(s, on); }

#endif // SECURITY_H 
