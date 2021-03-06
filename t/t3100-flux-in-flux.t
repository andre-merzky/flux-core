#!/bin/sh
#

test_description='Test that Flux can launch Flux'

. `dirname $0`/sharness.sh

# Size the session to one more than the number of cores, minimum of 4
SIZE=$(test_size_large)
test_under_flux ${SIZE}
echo "# $0: flux session size will be ${SIZE}"

ARGS="-o,-Sbroker.rc1_path=,-Sbroker.rc3_path=,--shutdown-grace=0.25"
test_expect_success "flux can run flux instance as a job" '
	run_timeout 10 flux mini run -n1 -N1 \
		flux start ${ARGS} flux getattr size >size.out &&
	echo 1 >size.exp &&
	test_cmp size.exp size.out
'

test_expect_success "flux subinstance leaves local_uri, remote_uri in KVS" '
	flux jobspec srun -n1 -N1 flux start /bin/true >j &&
	id=$(flux job submit j) &&
	flux job wait-event $id finish &&
	flux job info $id guest.flux.local_uri &&
	flux job info $id guest.flux.remote_uri
'

test_expect_success "flux --parent works in subinstance" '
	id=$(flux jobspec srun -n1 \
               flux start ${ARGS} flux --parent kvs put test=ok \
               | flux job submit) &&
	flux job attach $id &&
	flux job info $id guest.test > guest.test &&
	cat <<-EOF >guest.test.exp &&
	ok
	EOF
	test_cmp guest.test.exp guest.test
'

test_expect_success "flux --parent --parent works in subinstance" '
	id=$(flux jobspec srun -n1 \
              flux start ${ARGS} \
	      flux start ${ARGS} flux --parent --parent kvs put test=ok \
	      | flux job submit) &&
	flux job attach $id &&
	flux job info $id guest.test > guest2.test &&
	cat <<-EOF >guest2.test.exp &&
	ok
	EOF
	test_cmp guest2.test.exp guest2.test
'

test_expect_success "flux sets instance-level attribute" '
        level=$(flux mini run flux start ${ARGS} \
                flux getattr instance-level) &&
        level2=$(flux mini run flux start \
                 flux mini run flux start ${ARGS} \
                 flux getattr instance-level) &&
	level0=$(flux start ${ARGS} flux getattr instance-level) &&
        test "$level" = "1" &&
        test "$level2" = "2" &&
        test "$level0" = "0"
'

test_expect_success "flux sets jobid attribute" '
	id=$(flux jobspec srun -n1 \
		flux start ${ARGS} flux getattr jobid \
		| flux job submit) &&
	echo "$id" >jobid.exp &&
	flux job attach $id >jobid.out &&
	test_cmp jobid.exp jobid.out
'

test_done
