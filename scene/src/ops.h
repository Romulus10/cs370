set cross_product(set u, set v);

float dot_product(set u, set v);

set scalar_dot(float u, set v);

set pt_add(set a, set b);

set pt_sub(set a, set b);

float mag(set a);

bool check_sign_diff(float x, float y);

set get_normal(triangle i);

set get_intersect(set N, triangle i, set p1, set p2);
