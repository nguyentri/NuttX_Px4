/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/scripts/cm85/cm85_ipc_sections.ld
 *
 * Inter-Processor Communication (IPC) sections for dual-core
 * Shared memory region between CM85 and CM33
 *
 * CRITICAL: This memory MUST be configured as non-cacheable via MPU!
 ****************************************************************************/

SECTIONS
{
    /* IPC shared memory region - 64KB @ 0x220D0000 */
    .ipc_shmem (NOLOAD) :
    {
        __ipc_shmem_data_start = .;
        _sipc = ABSOLUTE(.);

        /* OpenAMP resource table */
        . = ALIGN(64);
        __resource_table_start = .;
        *(.resource_table)
        __resource_table_end = .;

        /* VirtIO vrings for bi-directional communication */
        . = ALIGN(64);
        __vring_start = .;

        . = ALIGN(64);
        __vring_tx_start = .;
        *(.vring_tx)
        __vring_tx_end = .;

        . = ALIGN(64);
        __vring_rx_start = .;
        *(.vring_rx)
        __vring_rx_end = .;

        __vring_end = .;

        /* Shared memory buffers */
        . = ALIGN(64);
        __shmem_buffers_start = .;
        *(.shmem_buffers)
        *(.ipc_buffer)
        *(.ipc_shmem)
        __shmem_buffers_end = .;

        /* Hardware semaphores */
        . = ALIGN(64);
        __hw_semaphores_start = .;
        *(.hw_semaphores)
        __hw_semaphores_end = .;

        /* Mailboxes */
        . = ALIGN(64);
        __mailbox_start = .;
        *(.mailbox)
        *(.mailbox_data)
        __mailbox_end = .;

        /* Message queues */
        . = ALIGN(64);
        __ipc_msgq_start = .;
        *(.ipc_msgq)
        *(.ipc_msgq_data)
        __ipc_msgq_end = .;

        _eipc = ABSOLUTE(.);
        __ipc_shmem_data_end = .;
    }> IPC_SHMEM_REGION
}
